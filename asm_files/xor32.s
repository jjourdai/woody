
# edi	pointer
# rsi	len
# edx	xor key

xor:
		call		test
test:
		pop rdi
		sub rdi, 0x103038 ; new entrypoint
		sub rdi, 0x19	; previous shellcode size
		add rdi, 0x31520  ; old entrypoint
		sub rdi, 0x5	; size of call test
		mov rcx, rsi

		call rdi

	.loop:
		cmp		rcx, 4
		jl		.end
		xor		[rdi], edx

		add		rdi, 4
		sub		rcx, 4
		jmp		.loop

	.end:
