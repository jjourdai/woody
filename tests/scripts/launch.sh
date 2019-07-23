#!/bin/sh

set -eux

UBUNTUS="xenial bionic cosmic disco eoan"
DEBIANS="jessie stretch buster"
ALPINES="3.7 3.8 3.9 3.10 edge"
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
	alpine)
		DIST="alpine"
		LIST="${ALPINES}"
		;;
	*)
		exit 1
		;;
esac

for img in $LIST; do
	docker build \
		--tag "${DIST}-${img}" \
		--build-arg "ARCH=${DIST}:${img}" \
		--build-arg ARCH_TYPE=${DIST} \
		-f tests/scripts/Dockerfile \
		.
	docker run --rm -t "${DIST}-${img}"
done
