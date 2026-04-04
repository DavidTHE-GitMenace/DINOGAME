from flask import Flask, request, jsonify
import sqlite3
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
DATABASE = "dino.db"

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    return conn

@app.route("/health")
def health():
    return {"status": "ok"}

# SIGNING UP
@app.route("/register", methods=["POST"]) 
# POST is usually used when you want to send data to the server
# for /register, that makes sense, because you’re sending a username and password

# GET = “give me data”
# POST = “here’s some data, do something with it”

def register():
    data = request.get_json()

    if not data:
        return jsonify({"error": "Request must be JSON"}), 400

    username = data.get("username")
    password = data.get("password")

    if not username or not password:
        return jsonify({"error": "Username and password are required"}), 400

    password_hash = generate_password_hash(password)

    conn = get_db_connection()
    cursor = conn.cursor()

    try:
        cursor.execute(
            "INSERT INTO users (username, password_hash) VALUES (?, ?)",
            (username, password_hash)
        )
        conn.commit()
    except sqlite3.IntegrityError:
        conn.close()
        return jsonify({"error": "Username already exists"}), 409
    
    # ALL ERRORS THAT COULD HAPPEN THAT ARE IMPORTANT:
    # sqlite3.IntegrityError for breaking a database rule like a UNIQUE constraint.
    # sqlite3.OperationalError for database-operation problems, like the DB path not being found or a transaction failing.
    # sqlite3.ProgrammingError for coding mistakes, like the wrong number of query parameters or using a closed connection.
    # sqlite3.Error as the broad parent class if you want one catch-all fallback.

    conn.close()
    return jsonify({"message": "User registered successfully"}), 201




# LOGGING IN
@app.route("/login", methods=["POST"]) 
def login():
    data = request.get_json() # takes in whatever JSON data from a client request hitting the API 
    if not data: # if data is missing or empty
        return jsonify({"error": "Request doesn't have anything in it"}), 400 # 400 is the HTTP status code for Bad Request

    # grabs the values from username and password
    username = data.get("username")
    password = data.get("password")


    if not username : # if the username is empty
        return jsonify({"error": "Username is empty"}), 400
    
    if not password: # if the password is empty
        return jsonify({"error": "Password is empty"}), 400    

    conn = get_db_connection() # opens a connection to the SQLite database and stores that connection in conn

    try:
        cursor = conn.cursor()
        # conn = the open connection to the database
        # cursor = the thing you use to actually send SQL commands through that connection

        cursor.execute( # use the database cursor to run an SQL command
            "SELECT password_hash FROM users WHERE username = ?",
            (username,)
        )
        user_row = cursor.fetchone() # gets a row from cursor, in this case there should only be one row


        if user_row is None: # if the username doesn't exist (returns blank from database)
            return jsonify({"error": "Invalid username or password"}), 401
            # don't need conn.commit() since we aren't changing anything in the database

        if not check_password_hash(user_row[0], password): # if the password the user put in doesn't match the password_hash that's in the database
            return jsonify({"error": "Invalid username or password"}), 401
        
    finally:
        conn.close() # close the connection

    return jsonify({"message": "Login was successful!"}), 200 # 200 is success code for login




# UPDATING THE SCORE
@app.route("/update_score", methods=["POST"]) 
def update_score():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Request doesn't have anything in it"}), 400
    
    username = data.get("username")
    score = data.get("score")

    if score is None:
        return jsonify({"error": "There is no score"}), 400
    
    if isinstance(score, str):
        if score == "":
            return jsonify({"error": "There is no score"}), 400
        score = score.strip()
        for i in score:
            if i not in "0123456789":
                return jsonify({"error": "Score isn't a number"}), 400
        score = int(score)
    
    if not username:
        return jsonify({"error": "There is no username"}), 400
    
    conn = get_db_connection()

    try:
        cursor = conn.cursor()
        cursor.execute(
            "SELECT best_score FROM users WHERE username = ?",
            (username,)
        )
        user_row = cursor.fetchone()

        if user_row is None:
            return jsonify({"error": "There is no score to compare to since the user wasn't found"}), 400
        
        if user_row[0] < score:
            cursor.execute(
                "UPDATE users SET best_score = ? WHERE username = ?",
                (score, username)
            )
            conn.commit()
            return jsonify({"message": "Score updated!"}), 200 

    finally:
        conn.close()

    return jsonify({"message": f"Score checked, best score unchanged. Score was {score}, and user's current score was {user_row[0]}"}), 200


if __name__ == "__main__":
    app.run(debug=True)