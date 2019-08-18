#!/bin/sh

set -eu

PROG_DIR="./tests/progs/"
PROGS=$(ls "${PROG_DIR}")
CIPHERS="xor8 xor16 xor32 rc5 rc4"

RET_CODE_NES="84"
## NES means Not Enough Space

_RED=$(tput setaf 1 2> /dev/null || echo "")
_GREEN=$(tput setaf 2 2> /dev/null || echo "")
_YELLOW=$(tput setaf 3 2> /dev/null || echo "")
_END=$(tput sgr0 2> /dev/null || echo "")

make re

__process() {
	exec="$1"
	name="$2"
	args="$3"
	ciph_mode="$4"
	DIFF=1
	WOODY=1

	printf "===== %-40s / %-10s : " "${name}" "${ciph_mode}"
	${exec} $args > /tmp/a 2>&1
	set +e
	./woody_woodpacker -c "${ciph_mode}" "${exec}" > /dev/null 2>&1
	if [ "$?" = "$RET_CODE_NES" ]; then
		set -e
		printf "%sNot enough space in binary %s\\n" "${_YELLOW}" "${_END}"
		return
	fi
	set -e
	./woody $args > /tmp/b 2>&1
	LINE=$(head -n 1 < /tmp/b)
	tail -n +2 < /tmp/b > /tmp/c
	if [ ! "${LINE}" = "....WOODY...." ]; then
		WOODY=0
	fi
	if ! diff /tmp/a /tmp/c; then
		DIFF=0
	fi
	rm -f /tmp/a /tmp/b /tmp/c
	rm -f woody
	TAG1="${_GREEN}OK${_END}"
	TAG2="${_GREEN}OK${_END}"
	if [ "$WOODY" = "0" ]; then TAG1="${_RED}KO${_END}"; fi
	if [ "$DIFF" = "0" ]; then TAG2="${_RED}KO${_END}"; fi
	printf "WOODY: %s, DIFF: %s\\n" "$TAG1" "$TAG2"
	if [ "$WOODY" = "0" ] || [ "$DIFF" = "0" ]; then
		exit 1
	fi
}

_process() {
	for ciph in $CIPHERS; do
		__process "$1" "$2" "$3" "$ciph"
	done
}

process() {
	for file in ${PROGS}; do
		file="${PROG_DIR}${file}"
		for flag in "" -no-pie "-pie -fPIC"; do
			gcc $flag -o tested "${file}"
			_process "./tested" "$(basename "${file}") $flag" ""
			rm -f tested
		done
	done

	_process /bin/ls "/bin/ls /bin /usr/bin" "/bin /usr/bin"
	_process /bin/date "/bin/date" "+%D"
	_process /bin/grep "/bin/grep 'include' -R /usr/include" "include -R /usr/include"
	_process /bin/grep "/bin/grep 'define' -R /usr/include" "define -R /usr/include"
	_process /bin/uname "/bin/uname -a" "-a"
	_process /bin/true "/bin/true" ""
	_process /usr/bin/find "/usr/bin/find /usr" "/usr"
	_process /usr/bin/wc "/usr/bin/wc /usr/include/stdlib.h" "/usr/include/stdlib.h"
	_process /usr/bin/env "/usr/bin/env" "-u _"
}

_tab() {
	CIPHER="$1"
	DIST="$2"
	ALL_FILES=""
	NB_FILES="0"
	NB_FILES_OK="0"
	NB_FILES_NES="0"
	NB_FILES_KO="0"


	PATH_SPACE=$(echo $PATH | tr ':' ' ')
	for path in $PATH_SPACE; do
		FILES=$(ls $path)
		for bin in $FILES; do
			set +e
			RET=$(file "$path/$bin" | grep ELF)
			set -e
			if [ ! "$RET" = "" ]; then
				NB_FILES=$((NB_FILES + 1))
				ALL_FILES="$ALL_FILES $path/$bin"
			fi
		done
	done

	for bin in $ALL_FILES; do
		set +e
		./woody_woodpacker -c "${CIPHER}" "${bin}" > /dev/null 2>&1
		RET="$?"
		set -e
		if [ "$RET" = "0" ]; then
			NB_FILES_OK=$((NB_FILES_OK + 1))
		elif [ "$RET" = "$RET_CODE_NES" ]; then
			NB_FILES_NES=$((NB_FILES_NES + 1))
		else
			NB_FILES_KO=$((NB_FILES_KO + 1))
		fi
		rm -f woody
	done

	printf "| %s | %s | %d | %d | %d | %d |\\n" "$DIST" "$CIPHER" "$NB_FILES" "$NB_FILES_OK" "$NB_FILES_NES" "$NB_FILES_KO" >> /tmp/out
}

tab() {
	rm -f /tmp/out
	touch /tmp/out
	for ciph in $CIPHERS; do
		_tab "$ciph" "$1"
	done
	cat /tmp/out
}

case $1 in
	process)
		process
		;;
	tab)
		tab "$2"
		;;
	*)
		exit 1
		;;
esac
