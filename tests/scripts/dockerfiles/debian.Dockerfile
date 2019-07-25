ARG	DIST
FROM debian:$DIST

RUN \
		apt-get update \
	&&	apt-get install -y \
			gcc \
			make \
			nasm

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ENTRYPOINT [ "./tests/scripts/run.sh" ]
