
# edi	pointer
# rsi	len
# edx	xor key

xor:
		mov rcx, rsi
	.loop:
		cmp		rcx, 4
		jl		.end
		xor		[rdi], edx

		add		rdi, 4
		sub		rcx, 4
		jmp		.loop

	.end:
