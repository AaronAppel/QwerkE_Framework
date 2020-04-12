git pull
echo Pulled latest
pause

rem commit local changes to local repo
set /p message=Commit message "..."?
git add .
git commit -m "%message%"
echo Commited local changes

rem push local commit up to master
git push
echo Pushed local commit(s)
pause