ARG	DIST
FROM archlinux/base

RUN \
		pacman -Syu --noconfirm \
	&&	pacman -S --noconfirm \
			gcc \
			make \
			nasm \
			diffutils \
			grep \
			libncurses-dev

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ENTRYPOINT [ "./tests/scripts/run.sh" ]
