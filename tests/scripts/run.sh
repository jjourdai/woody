#!/bin/sh

set -u

PROG_DIR="./tests/progs/"
PROGS=$(ls "${PROG_DIR}")
CIPHERS="xor8 xor16 xor32 rc5"

_RED=$(tput setaf 1 2> /dev/null || echo "")
_GREEN=$(tput setaf 2 2> /dev/null || echo "")
_YELLOW=$(tput setaf 3 2> /dev/null || echo "")
_END=$(tput sgr0 2> /dev/null || echo "")

make re

_process() {
	exec="$1"
	name="$2"
	args="$3"
	ciph_mode="$4"
	DIFF=1
	WOODY=1

	printf "===== %-40s / %-10s : " "${name}" "${ciph_mode}"
	${exec} $args > /tmp/a 2>&1
	./woody_woodpacker -c "${ciph_mode}" "${exec}" > /dev/null 2>&1
	if [ "$?" = "84" ]; then
		printf "%sNot enough space in binary %s\\n" "${_YELLOW}" "${_END}"
		return
	fi
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
	if [ "$WOODY" = "0" -o "$DIFF" = "0" ]; then
		exit 1
	fi
}

process() {
	for ciph in $CIPHERS; do
		_process "$1" "$2" "$3" "$ciph"
	done
}

for file in ${PROGS}; do
	file="${PROG_DIR}${file}"
	gcc -o tested "${file}"
	process "./tested" "$(basename "${file}")" ""
	rm -f tested
	gcc -no-pie -o tested "${file}"
	process "./tested" "$(basename "${file}") -no-pie" ""
	rm -f tested
done

process /bin/ls "/bin/ls /bin /usr/bin" "/bin /usr/bin"
process /bin/date "/bin/date" "+%D"
process /bin/grep "/bin/grep 'include' -R /usr/include" "include -R /usr/include"
process /bin/grep "/bin/grep 'define' -R /usr/include" "define -R /usr/include"
process /bin/uname "/bin/uname -a" "-a"
process /bin/true "/bin/true" ""
process /usr/bin/find "/usr/bin/find /usr" "/usr"
process /usr/bin/wc "/usr/bin/wc /usr/include/stdlib.h" "/usr/include/stdlib.h"
process /usr/bin/env "/usr/bin/env" "-u _"
