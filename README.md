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
4. Add Terraform for Infrastructure as Code
5. Add CI/CD with GitHub Actions
6. Add logging + monitoring
7. Build a React dashboard for leaderboard + stats
8. Use S3 for storing extra artifacts

DIFFICULTIES: Docker was easy to setup! Moving from SQLite to PostgreSQL took some time since I had to change the syntax, download a BETTER Database management tool (DBeaver), and make sure I understood what was going on. Not bad though, got distracted with social media though which made things take longer.