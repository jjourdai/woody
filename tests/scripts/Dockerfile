ARG	ARCH
FROM $ARCH

COPY	. /woody_woodpacker/

WORKDIR	/woody_woodpacker/

ARG	ARCH_TYPE
RUN		./tests/scripts/install.sh $ARCH_TYPE

ENTRYPOINT [ "./tests/scripts/run.sh" ]
