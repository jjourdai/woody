init:
	push	rax
	push	rdi
	push	rsi
	push	rdx
	push	rcx
	push	r8
	push	r9
	push	r10

	push rbp
	mov rbp, rsp
	call inject
	db "....WOODY....", 10

inject:
	pop rsi
	mov rdi, 1
	mov rdx , 14
	mov eax, 1
	syscall
	mov rsp, rbp
	pop rbp

	pop	r10
	pop	r9
	pop	r8
	pop	rcx
	pop	rdx
	pop	rsi
	pop	rdi
	pop	rax

