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

ANY OTHER DIRECTIONS: