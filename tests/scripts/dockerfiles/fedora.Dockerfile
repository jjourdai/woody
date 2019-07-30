ARG	DIST
FROM fedora:$DIST

RUN \
		yum update -y \
	&&	yum install -y \
			gcc \
			make \
			nasm \
			ncurses \
			ncurses-devel \
			file \
	&&	dnf update -y \
	&&	dnf install -y \
			findutils

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ENTRYPOINT [ "./tests/scripts/run.sh" ]
