
; el criterio de pase de parametros se igual al de gcc de 64 bit 
;el orden es rdi, rsi, rdx, r10, r8, r9 y el valor de retorno en rax
;el numero de systemcall se pasa por rax


GLOBLA writeString


section .text
writeString:
    mov rax, 1
    int 80h
    ret 

    






