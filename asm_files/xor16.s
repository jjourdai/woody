
# edi	pointer
# rsi	len
# edx	xor key

xor:
		mov rcx, rsi
	.loop:
		cmp		rcx, 2
		jl		.end
		xor		[rdi], dx

		add		rdi, 2
		sub		rcx, 2
		jmp		.loop

	.end:
