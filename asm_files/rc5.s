
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
		mov		[rsp + 0x70], r12	; save tot size of L array (bits)
		shr		r12, 3
		mov		[rsp + 0x78], r12	; save tot size of L array (bytes)

	.init_s_array:
		mov		rax, qword 0xb7e151628aed2a6b	; P
		mov		qword [rsp + 0x110], rax
		mov		qword [rsp + 0x0], qword 8
		mov		rbx, qword 0x9e3779b97f4a7c15	; Q

	.loop1:		; init S array
		mov		rcx, [rsp + 0x70]
		cmp		[rsp + 0x0], rcx
		jge		.end_loop1

		mov		rcx, rsp
		add		rcx, [rsp + 0x0]
		add		rcx, 0x110
		mov		rdx, rcx
		sub		rdx, 0x8
		mov		rdx, qword [rdx]

		mov		[rcx], rdx
		add		[rcx], rbx

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
		jl		.L1
		mov		qword [rsp + 0x8], 8
	.L1:
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

		inc		qword [rsp + 0x0]
		jmp		.loop2

	.end_loop2:

		mov		rax, [rsp + 0x68]
		inc		eax
		shl		eax, 1

		cmp		eax, 2
		jg		.L2
		mov		eax, 3

	.L2:

		mov		ebx, 3
		mul		ebx

		mov		qword [rsp + 0x0], rax		; tmp[0]
		mov		qword [rsp + 0x8], 0		; tmp[1]
		mov		qword [rsp + 0x10], 0		; tmp[2]
		mov		qword [rsp + 0x18], 0		; reg[0]
		mov		qword [rsp + 0x20], 0		; reg[1]

	.loop3:
		mov		rax, qword [rsp + 0x0]
		cmp		rax, 0
		je		.end_loop3
		dec		rax
		mov		qword [rsp + 0x0], rax

		mov		[rsp + 0x30], rsp
		add		qword [rsp + 0x30], 0x110
		mov		rax, qword [rsp + 0x8]
		shl		rax, 3
		add		qword [rsp + 0x30], rax		; construction of S + tmp[1]

		mov		rax, qword [rsp + 0x30]
		mov		rax, qword [rax]
		add		rax, qword [rsp + 0x18]
		add		rax, qword [rsp + 0x20]
		rol		rax, 3						; ROTL(S[tmp[1]] + reg[0] + reg[1], 3);

		mov		[rsp + 0x18], rax			; reg[0] <- rax
		mov		rbx, qword [rsp + 0x30]
		mov		[rbx], rax					; S[tmp[1]] <- rax

		mov		[rsp + 0x30], rsp
		add		qword [rsp + 0x30], 0x100
		mov		rax, qword [rsp + 0x10]
		shl		rax, 3
		add		qword [rsp + 0x30], rax		; construction of L + tmp[2]

		mov		rax, qword [rsp + 0x30]
		mov		rax, qword [rax]
		add		rax, qword [rsp + 0x18]
		add		rax, qword [rsp + 0x20]
		xor		rcx, rcx
		xor		rbx, rbx
		mov		rbx, qword [rsp + 0x18]
		mov		cl, bl
		mov		rbx, qword [rsp + 0x20]
		add		cl, bl
		rol		rax, cl						; ROTL(L[tmp[2]] + reg[0] + reg[1], reg[0] + reg[1]);

		mov		[rsp + 0x20], rax			; reg[1] <- rax
		mov		rbx, [rsp + 0x30]
		mov		[rbx], rax					; L[tmp[2]] <- rax

		mov		rax, [rsp + 0x8]
		inc		rax
		xor		rdx, rdx
		mov		rbx, [rsp + 0x78]

		div		ebx
		mov		[rsp + 0x8], rdx

		mov		rax, [rsp + 0x10]
		inc		rax
		xor		rdx, rdx
		mov		rbx, 2

		div		ebx
		mov		[rsp + 0x10], rdx

		jmp		.loop3

	.end_loop3:

	.loop4:

		mov		rax, [rsp + 0x58]
		cmp		rax, 16
		jl		.end_loop4

		mov		rbx, [rsp + 0x68]
		mov		[rsp + 0x0], rbx

		mov		rax, [rsp + 0x50]
		mov		rax, [rax]
		mov		[rsp + 0x10], rax

		mov		rbx, [rsp + 0x50]
		add		rbx, 8
		mov		rbx, [rbx]
		mov		[rsp + 0x18], rbx

	.loop4_bis:
		mov		rdx, [rsp + 0x0]
		cmp		rdx, 1
		jl		.end_loop4_bis

		mov		rdx, [rsp + 0x0]
		shl		rdx, 1
		inc		rdx
		shl		rdx, 3
		add		rdx, rsp
		add		rdx, 0x110
		mov		rdx, [rdx]

		mov		rax, [rsp + 0x18]
		sub		rax, rdx

		mov		rcx, [rsp + 0x10]
		ror		rax, cl
		xor		rax, rcx

		mov		[rsp + 0x18], rax

		mov		rdx, [rsp + 0x0]
		shl		rdx, 4
		add		rdx, rsp
		add		rdx, 0x110
		mov		rdx, [rdx]

		mov		rax, [rsp + 0x10]
		sub		rax, rdx

		mov		rcx, [rsp + 0x18]
		ror		rax, cl
		xor		rax, rcx

		mov		[rsp + 0x10], rax

		mov		rdx, [rsp + 0x0]
		dec		rdx
		mov		[rsp + 0x0], rdx
		jmp		.loop4_bis

	.end_loop4_bis:

		mov		rax, [rsp + 0x50]
		mov		rbx, [rsp + 0x10]
		mov		rcx, [rsp + 0x110]
		sub		rbx, rcx
		mov		[rax], rbx
		add		rax, 8
		mov		rbx, [rsp + 0x18]
		mov		rcx, [rsp + 0x118]
		sub		rbx, rcx
		mov		[rax], rbx
		add		rax, 8
		mov		[rsp + 0x50], rax

		mov		rax, [rsp + 0x58]
		sub		rax, 16
		mov		[rsp + 0x58], rax

		jmp		.loop4
	
	.end_loop4:

		leave
