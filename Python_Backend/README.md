MAKE SURE YOU RUN THIS WHILE YOU'RE IN THIS DIRECTORY: .\venv\Scripts\Activate.ps1

RUNNING TESTS / PUTTING IN USERS / CHECKING USERS:
Invoke-RestMethod -Uri http://127.0.0.1:5000/login `
  -Method POST `
  -ContentType "application/json" `
  -Body '{"username":"david","password":"mypassword"}'

Invoke-RestMethod -Uri http://127.0.0.1:5000/login -Method POST -ContentType "application/json" -Body '{"username":"isra","password":"YOUR_ACTUAL_PASSWORD_HERE"}'

ACCESSING THE DATABASE:
- Open DB Browser for SQLite on Windows
- Go to "Browse Data" tab
- Click dropdown and click "users" to see the table