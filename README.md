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


I'm going to have to make sure I get all of the GCP SDK terminal commands down in my notes:



This creates the actual managed PostgreSQL server in GCP (Cloud SQL PostreSQL instance):
gcloud sql instances create dino-postgres-cloud `
  --database-version=POSTGRES_15 `
  --tier=db-f1-micro `
  --region=us-central1

Then you create the database inside the server:
gcloud sql databases create dino_game --instance=dino-postgres-cloud

Then I create the user:
gcloud sql users create dino_user --instance=dino-postgres-cloud --password=YOUR_PASSWORD_HERE

Verify by showing the list of databases:
gcloud sql databases list --instance=dino-postgres-cloud

Showing the list of users:
gcloud sql users list --instance=dino-postgres-cloud



Your Google account
→ controls the GCP project, billing, Cloud Run, Cloud SQL settings

postgres user
→ default PostgreSQL admin/superuser-ish database account

dino_user
→ app-specific database user your Flask API uses

So I create the Cloud SQL PostreSQL instance and it's running, the I create the database, then the table.


Finding tables that are public:
SELECT table_name
FROM information_schema.tables
WHERE table_schema = 'public';

So I installed Google Cloud's SDK shell, opened it's terminal downloaded/set-up a bunch of stuff and enabled permissions for the database I'm making. I then make a Google Cloud instance, make a database within this instance, and the users table. The users table was made on the Google Cloud Console browser. And now I'm going to create an "Artifact Registry" repo that stores the Docker image with the environment of Python, Flask, etc.

Artifact Registry - where GCP stores my Docker image before Cloud Run deploys it

The line for Artifact Registry Repo: gcloud artifacts repositories create dino-api-repo --repository-format=docker --location=us-central1 --description="Dino Game API Docker images"

Now I'm pushing the Docker image to the GCP:
gcloud builds submit --tag us-central1-docker.pkg.dev/project-55e2d944-e84a-4201-98a/dino-api-repo/dino-api:latest .




Hit permissions wall when pushing the Docker image to GCP, I ran these commands:
gcloud projects add-iam-policy-binding project-55e2d944-e84a-4201-98a --member=serviceAccount:986544070781-compute@developer.gserviceaccount.com --role=roles/storage.objectViewer

gcloud projects add-iam-policy-binding project-55e2d944-e84a-4201-98a --member=serviceAccount:986544070781-compute@developer.gserviceaccount.com --role=roles/artifactregistry.writer

gcloud projects add-iam-policy-binding project-55e2d944-e84a-4201-98a --member=serviceAccount:986544070781-compute@developer.gserviceaccount.com --role=roles/logging.logWriter

storage.objectViewer       → lets Cloud Build read the uploaded source archive
artifactregistry.writer    → lets Cloud Build push the Docker image to Artifact Registry
logging.logWriter          → lets Cloud Build write build logs


Cloud Run - runs that Docker image as a live web API, starts the Flask API container

So now, after I've sent the Docker image into the Artifact Registry repo, I now need to also deploy the Docker image to something called "Cloud Run" and connecting "Cloud Run" to the Cloud SQL PostgreSQL database. Once I get all of this done, I'm going to summarize it all in one paragraph.

Vocab to make my understanding easier:
Artifact Registry = storage shelf for the packaged backend
Cloud Run = the machine/serverless service that actually runs the backend
Cloud SQL = the managed PostgreSQL database server

Cloud Run uses the Docker image stored in Artifact Registry to create/run the live API service.

Give Cloud Run permission to connect to Cloud SQL cmd line:
gcloud projects add-iam-policy-binding project-55e2d944-e84a-4201-98a --member=serviceAccount:986544070781-compute@developer.gserviceaccount.com --role=roles/cloudsql.client

Deploy the API to Cloud Run cmd line:
gcloud run deploy dino-api --image us-central1-docker.pkg.dev/project-55e2d944-e84a-4201-98a/dino-api-repo/dino-api:latest --region us-central1 --allow-unauthenticated --add-cloudsql-instances project-55e2d944-e84a-4201-98a:us-central1:dino-postgres-cloud --set-env-vars DB_HOST=/cloudsql/project-55e2d944-e84a-4201-98a:us-central1:dino-postgres-cloud,DB_NAME=dino_game,DB_USER=dino_user,DB_PASSWORD=YOUR_DINO_USER_PASSWORD,DB_PORT=5432

What this does:

Cloud Run service name: dino-api
Docker image: your image from Artifact Registry
Public access: allowed
Database connection: dino-postgres-cloud
Environment variables: DB_HOST, DB_NAME, DB_USER, DB_PASSWORD, DB_PORT

Cloud Run will give a public URL when it finishes deploying.

THIS IS THE URL: https://dino-api-986544070781.us-central1.run.app

If for SOME reason, I lose the URL, put this command in:
gcloud run services describe dino-api --region=us-central1 --format="value(status.url)"




5/27

Could you fucking believe it? SFML's HTTP is limiting me from accessing the API which uses HTTPS. That's fucked.
My C++ HTTP client can’t talk to it because Cloud Run uses HTTPS and sf::Http does not support HTTPS. Official SFML docs say sf::Http is a simple HTTP client and “The HTTPS protocol is not supported.” Even SFML 3’s docs still say HTTPS is not supported.
We are going to implement libcurl for HTTPS.

Well well well, we can't even install libcurl since we don't have the MSYS2 MinGW64 terminal, where you install libcurl. So I'm gonna install MSYS2.

We installed MSYS2, and installed libcurl in the MSYS2 terminal, then made curl
curl terminal command = testing API manually
libcurl = letting your C++ game make HTTPS API requests



Situation: When I deployed my Flask backend to GCP Cloud Run, my C++ SFML client could no longer use sf::Http because Cloud Run uses HTTPS and SFML’s HTTP client did not support HTTPS. 

Task: So I had to find a way to support GCP's HTTPS URL, so the API could work again with the new HTTPS URL.

Action: I first used the terminal curl command to verify the deployed API endpoints worked since I was changing URLs from my previous http URL to the new HTTPS URL the GCP SDK terminal gave me. I found that libcurl supports HTTPS URLs, so I want to integrate libcurl into the C++ client. But to install libcurl, I needed to have a MSYS2 terminal, which I didn't have at the time, so I installed MSYS2, opened the termincal, and installed libcurl using the command:  pacman -S mingw-w64-x86_64-curl
So now that I installed libcurl, I had to make the client request functions POST and GET for the API. So I made ApiClient.hpp that declares the API functions GET and POST, and ApiClient.cpp that defines how the GET and POST functions for /health, 
/login, /register, /update_score, and /high_score work using libcurl. So ApiClient.hpp exposes simple functions like postJsonToApi, and ApiClient.cpp handles the actual HTTPS request, JSON headers, CA certificate verification, response body capture, and HTTP status code retrieval. 

Result: That kept my main game code cleaner while allowing the game to communicate with the cloud backend securely again.


networking wrapper - A wrapper is just code that hides ugly/complicated code behind a cleaner function.
EXAMPLE: "ApiResponse response = postJsonToApi("/login", jsonBody);"
That function is the wrapper.

NOTES ON APICLIENT FILES:
curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
Means:
“Send the request to this URL.”


curl_easy_setopt(curl, CURLOPT_POST, 1L);
Means:
“This is a POST request.”


curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
Means:
“Here is the JSON data I’m sending.”


curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
Means:
“Here are the headers, like Content-Type: application/json.”


curl_easy_setopt(curl, CURLOPT_CAINFO, "ca-bundle.crt");
Means:
“Use this certificate file so HTTPS can be verified safely.”


curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
Means:
“When the server sends a response, use this function to collect the text.”


curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);
Means:
“Put the response text into response.body.”


curl_easy_perform(curl);
means:
“Actually send the request now.”



CHATGPT'S Cloud Upgrade Summary:
- Dockerized Flask REST API
- Migrated backend database from SQLite to PostgreSQL
- Created local PostgreSQL container with Docker Compose
- Deployed Docker image to GCP Artifact Registry
- Hosted Flask API on Cloud Run
- Created Cloud SQL PostgreSQL database
- Connected Cloud Run to Cloud SQL using environment variables
- Replaced SFML sf::Http with libcurl for HTTPS support
- Migrated local PostgreSQL user/high-score data into Cloud SQL
- Verified C++ game login and score updates through the cloud backend

I forgot what Flask was lol, here's what is incase I forget again:
Flask - the Python tool that lets app.py receive requests like /login, /register, /update_score

CONTRIBUTIONS: FINALLY got everything into the cloud and that entails:
              - Deployed Docker image to GCP Artifact Registry
              - Hosted Flask API on Cloud Run
              - Created Cloud SQL PostgreSQL database
              - Connected Cloud Run to Cloud SQL using environment variables
              - Replaced SFML sf::Http with libcurl for HTTPS support
              - Migrated local PostgreSQL user/high-score data into Cloud SQL
              - AND IT FUCKING WORKS.

CHALLENGES: Understanding EVERYTHING. Getting an understanding of all of this is fucking nuts. I'm so glad I wrote so much in my notes. I at least understand the general gist of everything I did for the past few days.




5/28

Right now, we are trying to make this game into something that people can download and play so I can actually get user data. So to make it so people play it in the most CONVIENENT way, I'm going to download Inno to wrap the CA file, all of the dll files, and assets into a executable that'll show up on a desktop just like any other app. Then we make a LinkedIn post with what I did, the game executable, and what I plan to do next. That would be some GOAT shit, and that would make this project one of the most DISGUSTING projects I've ever made. Resume icon right there.

The way you have this as an actual app, is to first get the executable and everything needed like that assets, dlls, and anything else that the executable needs to run the game/app properly. Nothing else by the way, just those things. Put all of it in a folder. Run a script in Inno Setup and you'll get the executable file, and you run it. It's not too bad.

I got the scipt for Inno Setup just in case I lose it somehow:
#define MyAppName "David's Dino Game"
#define MyAppVersion "1.0"
#define MyAppPublisher "David Baloyi"
#define MyAppExeName "DinoGame.exe"

[Setup]
AppId={{DINO-GAME-CLOUD-PLAYTEST-2026}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\Dino Game
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
SetupIconFile=C:\Users\dvdjr\OneDrive\Desktop\DinoGame Installer Source\DinoIcon.ico
OutputDir=C:\Users\dvdjr\OneDrive\Documents\PersonalProjects\Dino Game Contents\DinoInstallerOutput
OutputBaseFilename=DinoGameSetup
Compression=lzma
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; GroupDescription: "Additional shortcuts:"; Flags: checkedonce

[Files]
Source: "C:\Users\dvdjr\OneDrive\Desktop\DinoGame Installer Source\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\DinoIcon.ico"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\DinoIcon.ico"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "Launch Dino Game"; Flags: nowait postinstall skipifsilent

REALIZATION: I realize when I have an idea in mind, and someone/something suggests that I can't actually fufill that way of doing something and recommends something else, I disengage so hard. I then have to come in terms with the new idea and abandon my old idea which may take a bit depending on what it is. How do you come to terms with an idea that wasn't what you intially wanted to do, and you had another idea that felt right to you? And it didn't just feel right, but it felt like it may be possible to do if thought out more. Like both options are possible, but you want to do your option for various reasons. And why I mentioned this was because I wanted the executable to be just a quick click off my post, but people have to go a website, THEN download it. Wasn't messing with that.  

Something I must remember when turning any C++ program into an actual app, -mwindows needs to be added so the terminal is gone. But when I need to go back to my code -mwindows needs to go.