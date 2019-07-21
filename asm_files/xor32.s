
# edi	pointer
# rsi	len
# edx	xor key

xor:
		mov		rcx, rsi

	.loop:
		cmp		rcx, 4
		jl		.end
		xor		[edi], edx

		add		edi, 4
		sub		rcx, 4
		jmp		.loop

	.end:
