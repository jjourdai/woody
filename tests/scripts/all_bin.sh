#!/bin/bash

ALL_FILES=""
NB_FILES="0"

PATH_SPACE=$(echo $PATH | tr ':' ' ')
for path in $PATH_SPACE; do
	FILES=$(ls $path)
	for bin in $FILES; do
		RET=$(file "$path/$bin" | grep ELF)
		if [ ! "$RET" = "" ]; then
			NB_FILES=$((NB_FILES + 1))
			ALL_FILES="$ALL_FILES $path/$bin"
		fi
	done
done

echo $NB_FILES
