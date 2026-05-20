import sqlite3
import psycopg2

# SQLite database file
sqlite_conn = sqlite3.connect("dino.db")
sqlite_cursor = sqlite_conn.cursor()

# PostgreSQL database running in Docker
pg_conn = psycopg2.connect(
    host="localhost",
    port=5432,
    database="dino_game",
    user="dino_user",
    password="dino_password"
)
pg_cursor = pg_conn.cursor()

# Get users from SQLite
sqlite_cursor.execute("SELECT username, password_hash, best_score FROM users")
users = sqlite_cursor.fetchall()

# Insert users into PostgreSQL
for username, password_hash, best_score in users:
    pg_cursor.execute(
        """
        INSERT INTO users (username, password_hash, best_score)
        VALUES (%s, %s, %s)
        ON CONFLICT (username) DO NOTHING;
        """,
        (username, password_hash, best_score)
    )

pg_conn.commit()

sqlite_conn.close()
pg_conn.close()

print(f"Migrated {len(users)} users from SQLite to PostgreSQL.")