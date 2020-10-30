
GLOBAL userProgram: 
section .data
	buffer1 db "Hola en rojo",0 
    buffer2 db "hola en blanco",0
section .text
userProgram:    

    push rbp
    mov rbp, rsp
    
    mov rax, 1
    mov rdx, buffer1
    int 80h

    mov rax, 2
    mov rdx, buffer2
    int 80h

    mov rsp, rbp
    pop rbp
    ret




