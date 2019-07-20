
init:
	push	rax
	push	rbx
	push	rcx
	push	rdx
	push	rdi
	push	rsi

	push	rbp
	mov		rbp, rsp

	call	next
	db "....WOODY....", 10

next:
	mov		rdi, 1
	pop		rsi
	mov		rdx, 14
	mov		rax, 1
	syscall

	mov		rsp, rbp
	pop		rbp

	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rbx
	pop		rax
