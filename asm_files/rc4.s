
# rdi	pointer
# rsi	len
# rdx	key pointer

%define SIZE_PERMUTATION 256
%define KEY_SIZE 16

;section .text
;	global rc4
;	extern printf
;	extern _exit

rc4:
	push rbp
	mov rbp, rsp

	sub rsp, SIZE_PERMUTATION + 24
	and rsp, -16

	mov [rsp + 0], rdi		;	[rsp + 0] 	addr
	mov [rsp + 8], rsi		;	[rsp + 8]	length
	mov [rsp + 16], rdx		;	[rsp + 16]	key

.init_s:
	mov rdi, 0

.init_permutation:
	mov qword [rsp + 24 + rdi], rdi

;	mov rsi, rdi
;	mov rdx, [rsp + 24 + rdi]
;	push rdi
;	push rdx
;	lea rdi, [rel fmt_tmp.string]
;	call printf
;	pop rdx
;	pop rdi

	inc rdi
	cmp rdi, SIZE_PERMUTATION
	jne .init_permutation

	mov rdi, 0
	mov rsi, 0

.filled_permutation:
	;mov qword [rsp + 24 + rdi], rdi
	;add rsi, rsi
	add rsi, [rsp + 24 + rdi]

	mov rdx, 0
	mov rax, rdi
	mov rcx, KEY_SIZE
	div rcx

	mov rcx, [rsp + 16]
	mov rcx, [rcx + rdx]
	add rsi, rcx 
	and rsi, 0xff

;	push rsi
;	push rdi
;	lea rdi, [rel print_permut.string]
;	call printf
;	pop rdi
;	pop rsi

	mov rdx, [rsp + 24 + rdi]
	mov rcx, [rsp + 24 + rsi]
	mov [rsp + 24 + rsi], dl
	mov [rsp + 24 + rdi], cl

	inc rdi
	cmp rdi, SIZE_PERMUTATION
	jne .filled_permutation

	mov rdi, 0
.print_permutation:
	
;	mov rsi, [rsp + 24 + rdi]
;	push rdi
;	push rdi
;	lea rdi, [rel print_permut.string]
;	call printf
;	pop rdi
;	pop rdi

	inc rdi
	cmp rdi, SIZE_PERMUTATION
	jne .print_permutation

	mov rcx, 0
	mov r9, [rsp + 8]
	mov rdi, 0
	mov rsi, 0
.compute:
	
	inc rdi
	and rdi, 0xff

	add rsi, [rsp + 24 + rdi]
	and rsi, 0xff
	
	mov rdx, [rsp + 24 + rdi]
	mov r8, [rsp + 24 + rsi]
	mov [rsp + 24 + rdi], r8b
	mov [rsp + 24 + rsi], dl
		
	add r8, rdx
	and r8, 0xff
	mov r8, [rsp + 24 + r8]

	
	mov rdx, [rsp + 0]
	mov rdx, [rdx + rcx]
	xor  r8, rdx
	mov rdx, [rsp + 0]
	mov [rdx + rcx], r8b
	
;	push rdi
;	push rsi
;	push rcx
;	push r9
;	mov rsi, [rdx + rcx]
;	lea rdi, [rel print_permut.string]
;	call printf
;	pop r9
;	pop rcx
;	pop rsi
;	pop rdi

	inc rcx
	cmp rcx, r9
	jne .compute
	
.end:
	leave 
	;ret
	

;section .data:
;print_permut:
;	.string		db "%hhx ", 0
;fmt_tmp:
;	.string		db "S[%d] : %hhu", 10, 0
;fmtA:
;	.string		db "A : %016lx", 10, 0
;fmtB:
;	.string		db "B : %016lx", 10, 0
;fmtC:
;	.string		db "C : %016lx", 10, 0
;fmtD:
;      .string		db "D : %016lx", 10, 0
;fmtE:
;	.string		db "E : %016lx", 10, 0
;fmtF:
;	.string		db "F : %016lx", 10, 0
