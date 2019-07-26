#!/bin/sh

set -eux

UBUNTUS="xenial bionic cosmic disco eoan"
DEBIANS="stretch buster"
FEDORAS="26 27 28 29 30 31"
ARCHLINUX="base"
KALILINUX="base"
DIST=""

LIST=""

case $1 in
	ubuntu)
		DIST="ubuntu"
		LIST="${UBUNTUS}"
		;;
	debian)
		DIST="debian"
		LIST="${DEBIANS}"
		;;
	fedora)
		DIST="fedora"
		LIST="${FEDORAS}"
		;;
	archlinux)
		DIST="archlinux"
		LIST="${ARCHLINUX}"
		;;
	kalilinux)
		DIST="kalilinux"
		LIST="${KALILINUX}"
		;;
	*)
		exit 1
		;;
esac

for img in $LIST; do
	docker build \
		--tag "${DIST}-${img}" \
		--build-arg "DIST=${img}" \
		-f "tests/scripts/dockerfiles/${DIST}.Dockerfile" \
		.
	docker run --rm -t "${DIST}-${img}"
done