HOW TO COMPILE: make
HOW TO RUN: ./DinoGame.exe

GIT COMMANDS:
git switch -c your-branch-name 
(
    switch = move branches
    -c = create the branch first
    new-branch-name = whatever you want to call it
)

git add -A (this change is selected and ready to be included in the next commit)

git commit -m "update message" (saves all of your changes w/ a message of your own)

git push -u origin branch_name
(  
    push = send your commits to the remote repository
   -u = sets the default upstream branch, so future pushes can often just be git push
   origin = the name of your GitHub repository connection
   branch_name = the branch you’re pushing
)

git switch main (switches you to the main branch)


git add -A → prepare everything
git commit -m "..." → save it locally
git push -u origin branch-name → upload it to GitHub
git switch main → go back to main
git pull origin main → update main
git switch -c branch-name → make a new branch and enter it
git branch → see what branch you're on
git status → see's what branch you're on and if any files need to be comitted


5/19

If someone explains something to me and I STILL don't understand it, I'm the type of person to keep what they said in mind and later do research to find my own interpretation of it. Everyone has their own way of understanding/thinking/perspectives of things in life. I may need to find my own to not only gain my own undertanding, but to also be able to understand them as well.

Just installed Docker and learning what it means. Basically I'm making a Docker containment for my Python REST API Backend so whenever someone else runs my program, somewhere else on like their laptop or whatever device, they don't need to have install flask, or Python on their computer. Docker makes a container/house for that environment and mimicks the exact environment for other users who may not have certain things downloaded on their device, for the game to work.

Docker made a mini Linux environment, installed the Python packages from my requirements.txt, copied the backend files into the environment, then started app.py inside in the container

Unlike Docker, Kubernetes runs multiple containers across servers.

docker compose up --build: Docker started my Flask API container and then attached the terminal to the live logs.
Show me everything the backend is printing while it runs.

docker compose up --build -d: The -d means detached mode, so it runs in the background and gives my terminal back.
I can stop the docker with: docker compose down

You can test that the docker is working with: Invoke-RestMethod http://127.0.0.1:5000/health
Or just play the game

I can run things in the same terminal now!!! No more having to create a second terminal!

ACTUAL STEPS FOR THE FUTURE OF THIS PROJECT:
1. Containerize the backend with Docker ✓
2. Move from SQLite to PostgreSQL ✓
3. Deploy it to the cloud
    1. Use environment variables for DB_HOST, DB_NAME, DB_USER, DB_PASSWORD
    2. Use Gunicorn instead of Flask’s development server
    3. Make sure /health works
    4. Rebuild Docker locally
    5. Then deploy the API container to GCP Cloud Run
    6. Then connect it to Cloud SQL PostgreSQL
4. Add Terraform for Infrastructure as Code
5. Add CI/CD with GitHub Actions
6. Add logging + monitoring
7. Build a React dashboard for leaderboard + stats
8. Use S3 for storing extra artifacts

DIFFICULTIES: Docker was easy to setup! Moving from SQLite to PostgreSQL took some time since I had to change the syntax, download a BETTER Database management tool (DBeaver), and make sure I understood what was going on. Not bad though, got distracted with social media though which made things take longer.


5/26

The cloud needs something standardized to run. Docker gives it that standardized package. The cloud doesn't know how to run my project without proper instructions either. It's the same concept as running my game on another device. Docker gives the cloud the exact environment/container with the intructions to download Python, Flask, psycopg2, to copy my files like app.py and whatever else for the API and the server database to run in the background while users play the game. Plus, Docker is able to run my API, database server, and C++ Dino Game, all in one terminal so it's still a plus.

JUST FOUND THAT THESE ARE TWO DIFFERENT THINGS RUNNING NOW: API and POSTGRESQL SERVER
dino-api container        = runs your Flask API
dino-postgres container   = runs the PostgreSQL database server

SQLite:
My app opens a database file.

PostgreSQL:
My app connects to a running database server.

SQLite was having my API and database be one thing, which made it so I only had one server running. Now that I upgraded to PostgreSQL, PostgreSQL runs it's own database in another server, unlike SQLite, where the API was just interacting with a database file. My new PostgreSQL database is running in a server, and my Python Flask API is running in a server. Docker is able to make a virtual environment for both of these servers to run in one terminal (for convenience), and when this game is able to be ran on other devices and the cloud, Docker makes sure everything is downloaded and set up so the servers, and this game can run smoothly.

Four types of client requests: GET, POST, PUT, and DELETE

GET (Read): Retrieves data from a server. This is the most common request, used every time you load a webpage, view an image, or fetch information from a database. It only requests data and does not alter the server in any way.

POST (Create): Sends new data to a server to create a resource. For example, when you submit a web form, upload a file, or create a new user account, a POST request carries that new data to be saved on the server.

PUT (Update/Replace): Sends data to the server to completely update or replace an existing resource. If the resource does not already exist, the server may create it.

DELETE (Remove): Requests that the server remove a specific resource or piece of data at a given location.

Note: There are also supplementary methods like PATCH (used for making partial modifications to an existing resource) and OPTIONS (used to see what actions a server permits).

Why not contain the C++ Dino Game with Docker? Docker is usually strongest for things like:
APIs
web servers
databases
background workers
microservices

A desktop game is different because it needs a graphics window, keyboard input, audio, GPU/display access, etc. You can technically containerize GUI apps, but for a normal Windows SFML game, that is not the cleanest way to distribute it.

For your C++ game, the better “user can run this” solution is usually:
Package the .exe + SFML .dll files + assets into one release folder/zip

DinoGameRelease/
  DinoGame.exe
  sfml-graphics-2.dll
  sfml-window-2.dll
  sfml-system-2.dll
  sfml-audio-2.dll
  sfml-network-2.dll
  assets/
    fonts/
    images/
    audio/

Then a user does not need to install SFML separately. They just run your .exe, assuming I packaged the DLLs correctly.

Backend API = Dockerize it
Database for local dev = Dockerize it
Desktop game = Package it as a Windows release

Just realized that apparently the Cloud won't just copy the data or connect to my PostgreSQL database server that I made, I have to somehow transport all of my data that I have from my PostgreSQL database to a Google/Azure Cloud PostgreSQL database. 

REALIZATION: People on average I feel don't need to know all of the details/context to something in order to perform or continue with doing work, tasks, etc. I'm the type of person to get stuck on a term/phrase/acronym, or hear something I don't completely understand and need to know what that specifically means. If I hear something I don't understand completely within a lecture, conversation, article, or anything like that, I either ask or get stuck until I know what that thing is. I feel like if I don't know what that particular thing is no matter how small, I can't fully understand the topic that is being told to me. Small details are important to me. But it can also be an issue at times, I'm slower at starting things than others, and I might be last in figuring something out or getting something done than the average person. But in the end, I understand things better than the average person, and I'm able to communicate it better. There's rarely ever times that information is not important. I think whenever you communicate things to whoever, you need to make it so they don't end up being more confused by your explanation. It made me a better communicator understanding this. 

My workarounds for this is to assess how important this question is. Does it feel like a small, nitpicky, trivial question? Will I have the answer to my question as time goes on? Will I remember this question later? Is it stopping me from progressing? Is it something that'll take time to explain to me? Is it something I need to research on my own time? Does this person know the answer to my question? Will this person be able to explain this to me in a way that I will understand and I WON'T be more confused? All of these factors matter to how important the question is and its priority in that moment. It's a lot to think about, and there's even more factors I didn't mention. This is my weakness, that is technically a strength in its own way.


THOUGHTS: My thoughts about AI and it being used as a tool, some people use AI as a way to get things done in a way that required no effort. No thought, no questions, it's the same thing as getting the smart kid to do your homework for you. It's the way you see AI and the interest in the work that you're doing if you're going to learn anything. For me, this is a project I honestly want to do, and the AI is a guide/mentor on the questions I have and doesn't lead me astray. I don't feel limited to wasting its time, I don't feel any intimidation, it's like somebody who always has time to explain things to you who is also an expert in the topic you're struggling with. It's flexible to your brain, unlike a human who only has limited ways of explaining things to you. It's always available whenever you need it as well. It goes at your pace, you can step away whenever you want. That's how I see AI. An intelligent, adaptable, flexible mentor. My only problem is now, what if I'm not in a place where ChatGPT exists, and I have to understand a topic from a human being with the problems I mentioned? I'm not sure. (edit: I understand, it's basically what I'm doing, getting and understand info from ChatGPT, then actually doing it on my own)