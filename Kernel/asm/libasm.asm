
	GLOBAL cpuVendor
	GLOBAL getTimeInfo
	GLOBAL _readKey
	GLOBAL kbFlag

	GLOBAL _sti 
	GLOBAL _cli
	GLOBAL picMasterMask
	GLOBAL picSlaveMask

	;Handlers
	GLOBAL _ex00Handler
	GLOBAL _ex01Handler

	GLOBAL _irq00Handler  ;timer tick
	GLOBAL _irq01Handler  ;keyboard
	GLOBAL _irq08Handler  ;RTC
	GLOBAL _irq04Handler  ;Serial Port 1 and 3
	GLOBAL _irq05Handler  ;USB
	;las interupciones de software
	GLOBAL _irq80Handler
	GLOBAL _hlt
	
	extern  irqDispatcher
	extern  exDispatcher
	extern  int80Handler ;las interupciones de software
section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

_hlt:
	sti
	hlt
	ret

;recibe un 1byte donde cada uno de sus 8 bit representa una entrada del pic
;si la entrada esta en 1 se ignora al dispositivo
picMasterMask:   
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:   
	push rbp
    mov  rbp, rsp
    mov  ax, di  ; ax = mascara de 16 bits
    out 0A1h,al
    pop rbp
    retn


_sti:
	sti
	ret


_cli:   ;
	cli
	ret
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;Arguments rdi -> seconds, minutes or hours
;Returns eax -> the number
getTimeInfo:
  push rbp
  mov rbp, rsp

  push rbx
  push rcx

  mov rcx, 10
  mov rax, rdi
  out 70h, al
  in al, 71h
  mov bx, ax
  and ax, 0xF0
  and bx, 0x0F
  shr rax, 4
  mul rcx
  add ax, bx

  pop rcx
  pop rbx

  mov rsp, rbp
  pop rbp
  ret

_readKey:
	in al,64h
	test al,1
	jz .nothing
	mov rax, 0
	in al, 60h
	jmp .end
.nothing: 
	mov rax, 0
.end:
	retn

kbFlag:
    push rbp
    mov rbp, rsp
    mov rax,0
.loop:
    in al,0x64       
    and al,0x01       
    cmp al,0
    je .loop
    in al,0x60
       
    mov rsp, rbp
    pop rbp
    ret


;System call
_irq80Handler:
	pushState
	mov rdi, rax 
	mov rsi, rsp
	;add rsi, 14*8 ;que apunte al primer argumento
	call int80Handler
	
	popState
	iretq


; IRQ Interruptions
%macro irqHandlerMaster 1
	
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

_irq00Handler:
	irqHandlerMaster 0
	;pushState
	;mov rdi, 0
	;call irqDispatcher ; ejecutamos la rutina de interrupcion del tick original
	;mov rdi, rsp 
	;call scheduler_shortTerm
	;mov  rsp, rax 
	  ;singal pic EOI (enf of Interupt)
	;mov al, 20h 
	;out 20h, al 

	;popState
	;iretq

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;RTC
_irq08Handler:
	irqHandlerMaster 8


; Exceptions
%macro exHandlerMaster 1
	pushState

	mov rsi, rsp 
	add rsi, 15*8 ;rsi apunta a la direccion de retorno a la funcion que fallo
	mov rdx, rsp 
	add rdx, 15*8 
	add rdx, 3*8 ;rdx apunta a la direccion de stack de la funcion que fallo

	mov rdi, %1 ;pasaje de parametros
	call exDispatcher ;es una funcion de c ya programada 

	popState
	iretq
%endmacro


;DivByZero
_ex00Handler:
	exHandlerMaster 0

;invalid opcode
_ex01Handler:
	exHandlerMaster 1


