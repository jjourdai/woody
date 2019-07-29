ARG	DIST
FROM fedora:$DIST

RUN \
		yum update -y \
	&&	yum install -y \
			gcc \
			make \
			nasm \
	&&	dnf update -y \
	&&	dnf install -y \
			findutils \
			libncurses-dev

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ENTRYPOINT [ "./tests/scripts/run.sh" ]
