
section .data:
fmt:
	.string		db "%016lx", 10, 0

section .text:
	global rc5
	extern printf

# rdi	pointer
# rsi	len
# rdx	key pointer
# ecx	nb rounds

rc5:
		push	rbp
		mov		rbp, rsp
		sub		rsp, 0x20
		and		rsp, -16

		mov		[rsp + 0x0], rdi
		mov		[rsp + 0x8], rsi
		mov		[rsp + 0x10], rdx
		mov		[rsp + 0x18], rcx

		inc		ecx
		mov		eax, ecx
		mov		edx, 16
		mul		edx
		mov		r12, rax	; save size of S array
		mov		r15, rax	; stack allocation

		add		r15, 0x10	; add L size array
		add		r15, 0x100	; add some space to variables

		sub		rsp, r15	; allocate
		mov		rax, rsp
		add		rax, r15
		mov		rbx, [rax]
		mov		[rsp + 0x50], rbx	; save pointer
		add		rax, 8
		mov		rbx, [rax]
		mov		[rsp + 0x58], rbx	; save len
		add		rax, 8
		mov		rbx, [rax]
		mov		[rsp + 0x60], rbx	; save key pointer
		add		rax, 8
		mov		rbx, [rax]
		mov		[rsp + 0x68], rbx	; save nb rounds

	.init_s_array:
		mov		rax, qword 0xb7e151628aed2a6b	; P
		mov		qword [rsp + 0x110], rax
		mov		qword [rsp + 0x0], qword 8
		mov		rbx, qword 0x9e3779b97f4a7c15	; Q

	.loop1:		; init S array
		cmp		[rsp + 0x0], r12
		jge		.end_loop1

		mov		rcx, 0x110
		add		rcx, [rsp + 0x0]
		add		rcx, rsp
		mov		rdx, rcx
		sub		rdx, 0x8
		mov		rdx, qword [rdx]

		mov		[rcx], rdx
		add		[rcx], rbx

		; lea		rdi, [rel fmt.string]
		; mov		rsi, [rcx]
		; call	printf

		add		qword [rsp + 0x0], 8
		jmp		.loop1

	.end_loop1:

		; init L array
		mov		qword [rsp + 0x100], 0 ; L[0]
		mov		qword [rsp + 0x108], 0 ; L[1]
	
		mov		qword [rsp + 0x0], 0
	.loop2:
		cmp		qword [rsp + 0x0], 16
		je		.end_loop2

		mov		qword [rsp + 0x8], 0

		cmp		qword [rsp + 0x0], 8
		jl		.next_loop2
		mov		qword [rsp + 0x8], 8
	.next_loop2:
		mov		[rsp + 0x10], rsp
		add		qword [rsp + 0x10], 0x100
		mov		rbx, [rsp + 0x8]
		add		qword [rsp + 0x10], rbx

		mov		ebx, 4
		xor		edx, edx
		mov		eax, [rsp + 0x0]
		div		ebx

		mov		eax, edx
		mov		ebx, 8
		mul		ebx

		mov		cl, al

		mov		rbx, [rsp + 0x60]
		add		rbx, [rsp + 0x0]

		xor		rax, rax
		mov		al, [rbx]
		shl		eax, cl

		mov		rbx, [rsp + 0x10]

		add		[rbx], rax

		; lea		rdi, [rel fmt.string]
		; mov		rsi, [rbx]
		; call	printf

		inc		qword [rsp + 0x0]
		jmp		.loop2

	.end_loop2:

		mov		rax, [rsp + 0x68]
		inc		eax
		mov		ebx, 2
		mul		ebx

		cmp		eax, 2
		jg		.next_loop3
		mov		eax, 3

	.next_loop3:

		mov		ebx, 3
		mul		ebx

		; mov		qword [rsp + 0x0], rax
		mov		qword [rsp + 0x0], 2
		mov		qword [rsp + 0x8], 0
		mov		qword [rsp + 0x10], 0
		mov		qword [rsp + 0x18], 0
		mov		qword [rsp + 0x20], 0

	.loop3:
		mov		rax, qword [rsp + 0x0]
		cmp		rax, 0
		je		.end_loop3
		dec		rax
		mov		qword [rsp + 0x0], rax

		mov		[rsp + 0x30], rsp
		add		qword [rsp + 0x30], 0x110
		mov		rax, qword [rsp + 0x8]
		add		qword [rsp + 0x30], rax

		mov		rbx, qword [rsp + 0x30]
		lea		rdi, [rel fmt.string]
		mov		rsi, [rbx]
		call	printf

		mov		rbx, qword [rsp + 0x30]
		mov		rax, qword [rbx]
		add		rax, qword [rsp + 0x18]
		add		rax, qword [rsp + 0x20]
		rol		rax, 3

		lea		rdi, [rel fmt.string]
		mov		rsi, rax
		call	printf

		jmp		.loop3

	.end_loop3:

		mov		rax, 0
		mov		rsp, rbp
		pop		rbp
		ret
