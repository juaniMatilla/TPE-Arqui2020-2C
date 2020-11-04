

    GLOBAL SystemCall00
    GLOBAL SystemCall01
    GLOBAL SystemCall02
    GLOBAL SystemCall03
    GLOBAL SystemCall04
    GLOBAL SystemCall05
    GLOBAL SystemCall06
    GLOBAL SystemCall07

section .text

%macro SystemCall 1
	mov rax, %1
    int 80h
    ret 
%endmacro
SystemCall00:       ;writeString
    SystemCall 0
SystemCall01:       ;writeChar
   SystemCall 1
SystemCall02:       ;setConsoleSize
    SystemCall 2
SystemCall03:       ;drawFont16x16
    SystemCall 3
SystemCall04:       ;clearDisplay
    SystemCall 4
SystemCall05:       ;getKeyPressed
    SystemCall 5
SystemCall06:       ;nada
    SystemCall 6
SystemCall07:       ;nada
    SystemCall 7






