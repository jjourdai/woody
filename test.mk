
LAUNCH = ./tests/scripts/launch.sh

all: ubuntu debian

.PHONY: ubuntu
ubuntu:
	$(LAUNCH) ubuntu

.PHONY: debian
debian:
	$(LAUNCH) debian
