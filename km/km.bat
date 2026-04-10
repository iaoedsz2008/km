@echo off

set "svc=%~n0"

sc create "%svc%" binPath= "%~dpn0.sys" type= kernel
sc start "%svc%"
pause

sc stop "%svc%"
sc delete "%svc%"
pause
