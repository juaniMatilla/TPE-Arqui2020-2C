
; el criterio de pase de parametros se igual al de gcc de 64 bit 
;el orden es rdi, rsi, rdx, r10, r8, r9 y el valor de retorno en rax
;el numero de systemcall se pasa por rax


GLOBAL SystemCall00
GLOBAL SystemCall01
GLOBAL SystemCall02
GLOBAL SystemCall03

section .text
SystemCall00:
    mov rax, 0
    int 80h
    ret 

SystemCall01:
    mov rax, 1
    int 80h
    ret 

;SystemCall02:  //matriz
    ;mov rax, 2
    ;int 80h
    ;ret 

SystemCall03:
    mov rax, 3
    int 80h
    ret 






