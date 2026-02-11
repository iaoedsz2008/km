@echo off

sc create ZwCreateSection binPath= "%~dp0\ZwCreateSection.sys" type= kernel
sc start ZwCreateSection
pause

sc stop ZwCreateSection
sc delete ZwCreateSection
pause
