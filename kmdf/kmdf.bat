@echo off

sc create kmdf binPath= "%~dp0\kmdf.sys" type= kernel
sc start kmdf
pause

sc stop kmdf
sc delete kmdf
pause
