
D:\Downloads\nasm-2.16.01\nasm.exe -f bin ISR32.asm
REM D:\Downloads\nasm-2.16.01\ndisasm.exe -b 32 -o 0x00 ISR32

D:\Downloads\nasm-2.16.01\nasm.exe -f bin ISR64.asm
REM D:\Downloads\nasm-2.16.01\ndisasm.exe -b 64 -o 0x00 ISR64

%SystemRoot%\System32\PING.EXE -n 88 127.0.0.1 >nul
