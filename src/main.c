#include "woody.h"

static void	build_shellcode(t_shellcode *sh)
{
	sh_regs_save(sh);
	sh_initframe(sh);
	switch (g_env.flag.cipher_type) {
		case XOR_32:
			g_env.asm_file = XOR32_ASMFILE;
			verify_key(&g_env.key.xor32, sizeof(g_env.key.xor32));
			sh_xor(sh, g_env.key.xor32, X32);
			break;
		case XOR_16:
			g_env.asm_file = XOR16_ASMFILE;
			verify_key(&g_env.key.xor16, sizeof(g_env.key.xor16));
			sh_xor(sh, g_env.key.xor16, X16);
			break;
		case XOR_8:
			g_env.asm_file = XOR8_ASMFILE;
			verify_key(&g_env.key.xor8, sizeof(g_env.key.xor8));
			sh_xor(sh, g_env.key.xor8, X8);
			break;
		case RC5:
			g_env.asm_file = RC5_ASMFILE;
			verify_key(&g_env.key.rc5, sizeof(g_env.key.rc5));
			sh_rc5(sh, g_env.key.rc5);
			break;
		default:
			printf("NOT HANDLED\n"); exit(EXIT_FAILURE);
			break;
	}
	sh_print(sh, "....WOODY....\n", 14);
	sh_endframe(sh);
	sh_regs_recover(sh);
	sh_jump(sh);
}

int		main(int argc, char **argv)
{
	ft_bzero(&g_env, sizeof(g_env));
	g_env.exit_code = WOODY_OK;
	get_options(argc, argv);
	if (g_env.flag.filename == NULL) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}	
	if (!(g_env.flag.value & F_CIPHER)) {
		g_env.flag.cipher_type = DEFAULT_ALGO;
	}
	g_env.shellcode = sh_alloc();
	build_shellcode(g_env.shellcode);
	printf("filename : %s\n", g_env.flag.filename);
	pack_this_file(g_env.flag.filename);
	sh_free(g_env.shellcode);
	return (g_env.exit_code);
}
