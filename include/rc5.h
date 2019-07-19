#ifndef RC5_H
#define RC5_H

#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

/* sources:
**
**	http://x.heurtebise.free.fr/Enseignements/ATER/S4/Crypto/PDF/Crypto_CM_chap1.pdf
**	http://sdz.tdct.org/sdz/les-premiers-algorithmes-de-chiffrement.html
**	https://tools.ietf.org/html/rfc2040
**	https://people.csail.mit.edu/rivest/Rivest-rc5rev.pdf
**	https://www.geeksforgeeks.org/computer-network-rc5-encryption-algorithm/
**
*/

void		rc5_encrypt(void *data, size_t len, void *dest);

/*
**	3 Parameters
**
**	NB_ROUNDS	variable
**	WORD_SIZE	fixed to 8bytes (64bits)
**	KEY_SIZE	variable (in bytes)
*/

#define NB_ROUNDS		32
#define KEY_SIZE		16

// CONSTANTS

#define	P				0xb7e151628aed2a6b
#define Q				0x9e3779b97f4a7c15
#define S_SIZE			(2 * (NB_ROUNDS + 1))
#define L_SIZE			(KEY_SIZE + 8 - 1) / 8

// Helpers

#define ROTL(x, s)	((uint64_t)(((x) << (s)) | ((x) >> (64 - (s)))))
#define ROTR(x, s)	((uint64_t)(((x) >> (s)) | ((x) << (64 - (s)))))

#endif
