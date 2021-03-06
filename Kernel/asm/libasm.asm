
	GLOBAL cpuVendor
	GLOBAL getTimeInfo
	GLOBAL getMemoryValue
	GLOBAL getKeyScanCode
	GLOBAL saveInitialRSP

	GLOBAL _sti 
	GLOBAL _cli
	GLOBAL _hlt
	GLOBAL _rsp
	GLOBAL picMasterMask
	GLOBAL picSlaveMask

	;Handlers
	GLOBAL _ex00Handler
	GLOBAL _ex01Handler

	GLOBAL _irq00Handler  ;timer tick
	GLOBAL _irq01Handler  ;keyboard
	GLOBAL _irq08Handler  ;RTC

	;las interupciones de software
	GLOBAL _irq80Handler
	GLOBAL _irq81Handler:
	
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
	pop r14 ;
	pop r13 
	pop r12 
	pop r11 ;
	pop r10 ;
	pop r9 ;
	pop r8 ;
	pop rsi ;
	pop rdi ;
	pop rbp ;
	pop rdx ;
	pop rcx ;
	pop rbx 
	pop rax ;
%endmacro

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
    out  0A1h,al
    pop rbp
    retn
_sti:
	sti
	ret

_cli:   
	cli
	ret

_hlt:
	sti
	hlt
	ret

_rsp:
	mov rax, rsp
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

getKeyScanCode:
	push rbp
	mov rbp,rsp

	mov rax,0
	in al,64h
	and al,01h
	out 64h,al
	in al,60h

	mov rsp,rbp
	pop rbp
	ret

getMemoryValue:	
	push rbp
	mov rbp,rsp
	
	mov rax, 0
	mov al,byte[rdi]

	mov rsp,rbp
	pop rbp
	ret


;System call
_irq80Handler:
	pushState

	mov rdi, rax 
	mov rsi, rsp
	call int80Handler
	
	popState
	iretq

; IRQ Interruptions
%macro irqHandlerMaster 1
	
	;mov rsi, rsp 	;direcion donde ocurrio la expcion
	pushState

	mov rdi, %1 	; pasaje de parametro
	mov rsi, rsp   	; direccion del stack pointer para obtener los registros
	;mov rcx, rsp 
	;add rcx, 18*8 	;apunta a la direcion de rsp
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
	
%endmacro

_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;RTC
_irq08Handler:
	irqHandlerMaster 8


; Exceptions
%macro exHandlerMaster 1
	;mov rsi, rsp 	;direcion donde ocurrio la expcion
	pushState

	mov rdi, %1 	; pasaje de parametro
	mov rsi, rsp   	; direccion del stack pointer para obtener los registros
	;mov rcx, rsp 
	;add rcx, 18*8 	;apunta a la direcion de rsp
	call exDispatcher 

	popState
	iretq
%endmacro

;DivByZero
_ex00Handler:
	exHandlerMaster 0
;invalid opcode
_ex01Handler:
	exHandlerMaster 1
