
LAUNCH = ./tests/scripts/launch.sh

.PHONY: all
all: ubuntu debian fedora archlinux kalilinux

.PHONY: ubuntu
ubuntu:
	$(LAUNCH) ubuntu

.PHONY: debian
debian:
	$(LAUNCH) debian

.PHONY: fedora
fedora:
	$(LAUNCH) fedora

.PHONY: archlinux
archlinux:
	$(LAUNCH) archlinux

.PHONY: kalilinux
kalilinux:
	$(LAUNCH) kalilinux
