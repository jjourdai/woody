ARG	DIST
FROM ubuntu:$DIST

RUN \
		apt-get update \
	&&	apt-get install -y \
			gcc \
			make \
			nasm \
			libncurses-dev \
			file

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ENTRYPOINT [ "./tests/scripts/run.sh" ]
