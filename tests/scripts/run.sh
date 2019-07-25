#!/bin/sh

set -eu

PROG_DIR="./tests/progs/"
PROGS=$(find ${PROG_DIR} -name "*.c" | sort)

_RED=$(tput setaf 1 2> /dev/null || echo "")
_GREEN=$(tput setaf 2 2> /dev/null || echo "")
_END=$(tput sgr0 2> /dev/null || echo "")

make re

process() {
	exec="$1"
	name="$2"
	args="$3"
	DIFF=1
	WOODY=1

	printf "===== %-40s : " "${name}"
	${exec} $args > /tmp/a 2>&1
	./woody_woodpacker "${exec}" > /dev/null 2>&1
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
}

for file in ${PROGS}; do
	gcc -o tested "${file}"
	process "./tested" "$(basename "${file}")" ""
	rm -f tested
	gcc -no-pie -o tested "${file}"
	process "./tested" "$(basename "${file}") -no-pie" ""
	rm -f tested
done

process /bin/ls "/bin/ls /bin /usr/bin" "/bin /usr/bin"
process /bin/date "/bin/date" ""
process /bin/grep "/bin/grep 'include' -R /usr/include" "include -R /usr/include"
process /bin/grep "/bin/grep 'define' -R /usr/include" "define -R /usr/include"
process /bin/uname "/bin/uname -a" "-a"
process /bin/true "/bin/true" ""
process /usr/bin/find "/usr/bin/find /usr" "/usr"
process /usr/bin/wc "/usr/bin/wc /usr/include/stdlib.h" "/usr/include/stdlib.h"
process /usr/bin/env "/usr/bin/env" ""
