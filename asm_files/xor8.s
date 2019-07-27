
# edi	pointer
# rsi	len
# edx	xor key

xor:
		mov rcx, rsi
	.loop:
		cmp		rcx, 1
		jl		.end
		xor		[rdi], dl

		add		rdi, 1
		sub		rcx, 1
		jmp		.loop

	.end:
