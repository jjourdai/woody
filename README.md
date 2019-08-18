# woody [![Build Status](https://travis-ci.org/jjourdai/woody.svg?branch=master)](https://travis-ci.org/jjourdai/woody)

Le but est de coder un programme qui aura pour tâche, dans un premiertemps, de chiffrer un programme passé en paramètre. Seuls les ELF 64 bits seront traitésici.Un nouveau programme "woody" sera alors généré à la fin de l’exécution du pro-gramme. Lorsque ce nouveau programme (woody) sera exécuté, il devra se déchiffrerpour pouvoir se lancer. Son exécution sera identique en tout point avec le premier pro-gramme passé en paramétre à l’étape précédente.

Nous avons implémenté 5 algorithmes de chiffrages différents (dont 3 triviaux). Il s'agit de cryptages xor (sur 8, 16 et 32 bits) ainsi que les algorithmes de chiffrement rc4 et rc5.

Voici un tableau qui récapitule les capacités de notre programme sur plusieurs distributions:

Ce tableau est généré (hormis le header avec la commande make dist_tab).

| OS-DIST | CIPHER | Tot  | Success | Not enough space | Crash |
|:------------ |:----:|:--- |:---    |:---             |:---- |
| ubuntu-xenial | xor8 | 381 | 371 | 10 | 0 |
| ubuntu-xenial | xor16 | 381 | 371 | 10 | 0 |
| ubuntu-xenial | xor32 | 381 | 371 | 10 | 0 |
| ubuntu-xenial | rc5 | 381 | 277 | 104 | 0 |
| ubuntu-xenial | rc4 | 381 | 343 | 38 | 0 |
| ubuntu-bionic | xor8 | 357 | 354 | 3 | 0 |
| ubuntu-bionic | xor16 | 357 | 354 | 3 | 0 |
| ubuntu-bionic | xor32 | 357 | 354 | 3 | 0 |
| ubuntu-bionic | rc5 | 357 | 279 | 78 | 0 |
| ubuntu-bionic | rc4 | 357 | 332 | 25 | 0 |
| ubuntu-cosmic | xor8 | 357 | 355 | 2 | 0 |
| ubuntu-cosmic | xor16 | 357 | 355 | 2 | 0 |
| ubuntu-cosmic | xor32 | 357 | 355 | 2 | 0 |
| ubuntu-cosmic | rc5 | 357 | 335 | 22 | 0 |
| ubuntu-cosmic | rc4 | 357 | 354 | 3 | 0 |
| ubuntu-disco | xor8 | 722 | 722 | 0 | 0 |
| ubuntu-disco | xor16 | 722 | 722 | 0 | 0 |
| ubuntu-disco | xor32 | 722 | 722 | 0 | 0 |
| ubuntu-disco | rc5 | 722 | 716 | 6 | 0 |
| ubuntu-disco | rc4 | 722 | 722 | 0 | 0 |
| ubuntu-eoan | xor8 | 722 | 722 | 0 | 0 |
| ubuntu-eoan | xor16 | 722 | 722 | 0 | 0 |
| ubuntu-eoan | xor32 | 722 | 722 | 0 | 0 |
| ubuntu-eoan | rc5 | 722 | 714 | 8 | 0 |
| ubuntu-eoan | rc4 | 722 | 722 | 0 | 0 |
| debian-stretch | xor8 | 350 | 340 | 10 | 0 |
| debian-stretch | xor16 | 350 | 340 | 10 | 0 |
| debian-stretch | xor32 | 350 | 340 | 10 | 0 |
| debian-stretch | rc5 | 350 | 259 | 91 | 0 |
| debian-stretch | rc4 | 350 | 316 | 34 | 0 |
| debian-buster | xor8 | 357 | 357 | 0 | 0 |
| debian-buster | xor16 | 357 | 357 | 0 | 0 |
| debian-buster | xor32 | 357 | 357 | 0 | 0 |
| debian-buster | rc5 | 357 | 353 | 4 | 0 |
| debian-buster | rc4 | 357 | 356 | 1 | 0 |
| fedora-26 | xor8 | 878 | 868 | 10 | 0 |
| fedora-26 | xor16 | 878 | 866 | 12 | 0 |
| fedora-26 | xor32 | 878 | 868 | 10 | 0 |
| fedora-26 | rc5 | 878 | 682 | 196 | 0 |
| fedora-26 | rc4 | 878 | 816 | 62 | 0 |
| fedora-27 | xor8 | 870 | 846 | 24 | 0 |
| fedora-27 | xor16 | 870 | 846 | 24 | 0 |
| fedora-27 | xor32 | 870 | 846 | 24 | 0 |
| fedora-27 | rc5 | 870 | 674 | 196 | 0 |
| fedora-27 | rc4 | 870 | 794 | 76 | 0 |
| fedora-28 | xor8 | 866 | 848 | 18 | 0 |
| fedora-28 | xor16 | 866 | 848 | 18 | 0 |
| fedora-28 | xor32 | 866 | 848 | 18 | 0 |
| fedora-28 | rc5 | 866 | 644 | 222 | 0 |
| fedora-28 | rc4 | 866 | 800 | 66 | 0 |
| fedora-29 | xor8 | 1032 | 1032 | 0 | 0 |
| fedora-29 | xor16 | 1032 | 1032 | 0 | 0 |
| fedora-29 | xor32 | 1032 | 1032 | 0 | 0 |
| fedora-29 | rc5 | 1032 | 1020 | 12 | 0 |
| fedora-29 | rc4 | 1032 | 1030 | 2 | 0 |
| fedora-30 | xor8 | 844 | 844 | 0 | 0 |
| fedora-30 | xor16 | 844 | 844 | 0 | 0 |
| fedora-30 | xor32 | 844 | 844 | 0 | 0 |
| fedora-30 | rc5 | 844 | 842 | 2 | 0 |
| fedora-30 | rc4 | 844 | 844 | 0 | 0 |
| archlinux-base | xor8 | 2600 | 2592 | 8 | 0 |
| archlinux-base | xor16 | 2600 | 2592 | 8 | 0 |
| archlinux-base | xor32 | 2600 | 2592 | 8 | 0 |
| archlinux-base | rc5 | 2600 | 2488 | 112 | 0 |
| archlinux-base | rc4 | 2600 | 2568 | 32 | 0 |
| kalilinux-base | xor8 | 471 | 470 | 1 | 0 |
| kalilinux-base | xor16 | 471 | 470 | 1 | 0 |
| kalilinux-base | xor32 | 471 | 470 | 1 | 0 |
| kalilinux-base | rc5 | 471 | 462 | 9 | 0 |
| kalilinux-base | rc4 | 471 | 469 | 2 | 0 |
