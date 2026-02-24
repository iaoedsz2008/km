
nasm -f bin ISR32.asm
REM ndisasm -b 32 -o 0x00 ISR32

nasm -f bin ISR64.asm
REM ndisasm -b 64 -o 0x00 ISR64

%SystemRoot%\System32\PING.EXE -n 88 127.0.0.1 >nul
