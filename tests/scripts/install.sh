#!/bin/sh

case $1 in
	ubuntu|debian)
		apt-get update
		apt-get install -y gcc make nasm
		;;
	alpine)
		apk update
		apk add gcc make nasm libc-dev
		;;
	*)
		exit 1
		;;
esac
