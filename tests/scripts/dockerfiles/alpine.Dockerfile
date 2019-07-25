ARG	DIST
FROM alpine:DIST

RUN \
		apk update \
	&&	apk add \
			gcc \
			make \
			nasm \
			libc-dev

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ENTRYPOINT [ "./tests/scripts/run.sh" ]
