
LAUNCH = ./tests/scripts/launch.sh

all: ubuntu alpine

.PHONY: ubuntu
ubuntu:
	$(LAUNCH) ubuntu

.PHONY: debian
debian:
	$(LAUNCH) debian

.PHONY:
alpine:
	$(LAUNCH) alpine
