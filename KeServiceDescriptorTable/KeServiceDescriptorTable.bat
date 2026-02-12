@echo off

sc create KeServiceDescriptorTable binPath= "%~dp0\KeServiceDescriptorTable.sys" type= kernel
sc start KeServiceDescriptorTable
pause

sc stop KeServiceDescriptorTable
sc delete KeServiceDescriptorTable
pause
