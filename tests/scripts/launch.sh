#!/bin/sh

set -eux

UBUNTUS="xenial bionic cosmic disco eoan"
DEBIANS="jessie stretch buster"
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
