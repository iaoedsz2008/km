
@ECHO OFF

SETLOCAL ENABLEDELAYEDEXPANSION

FOR /F "TOKENS=*" %%X IN ('DIR /S /B
"CmRegisterCallback"
"ExQueueWorkItem"
"ExRegisterCallback"
"IoRegisterShutdownNotification"
"KeGenericCallDpc"
"KeIpiGenericCall"
"KeRegisterBugCheckCallback"
"KeRegisterNmiCallback"
"KeServiceDescriptorTable"
"KeSetSystemGroupAffinityThread"
"KeStackAttachProcess"
"KeSynchronizeExecution"
"KeWaitForMultipleObjects"
"KeWaitForSingleObject"
"kmdf"
"MmAllocateContiguousMemory"
"ObRegisterCallbacks"
"ProbeForRead"
"ProbeForWrite"
"PsCreateSystemThread"
"PspCidTable"
"PsSetCreateProcessNotifyRoutine"
"PsSetCreateThreadNotifyRoutine"
"PsSetLoadImageNotifyRoutine"
"Support"
"ZwCreateFile"
"ZwCreateSection"
') DO (
  SET "FullPath=%%X"
  SET "Extension=%%~xX"
  SET "Hit=0"

  IF "!Extension!"==".c" SET "Hit=1"
  IF "!Extension!"==".cpp" SET "Hit=1"
  IF "!Extension!"==".cxx" SET "Hit=1"
  IF "!Extension!"==".h" SET "Hit=1"
  IF "!Extension!"==".hpp" SET "Hit=1"
  IF "!Extension!"==".hxx" SET "Hit=1"

  IF "!Hit!"=="1" (
    ECHO %%X
    clang-format -i !FullPath!
  )
)

%SystemRoot%\System32\PING.EXE -n 3 127.0.0.1 >NUL
