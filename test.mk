
LAUNCH = ./tests/scripts/launch_dockers.sh
CMD = process
VOL_TAB = ""

.PHONY: all
all: ubuntu debian fedora archlinux kalilinux

.PHONY: ubuntu
ubuntu:
	$(LAUNCH) $(CMD) ubuntu $(VOL_TAB)

.PHONY: debian
debian:
	$(LAUNCH) $(CMD) debian $(VOL_TAB)

.PHONY: fedora
fedora:
	$(LAUNCH) $(CMD) fedora $(VOL_TAB)

.PHONY: archlinux
archlinux:
	$(LAUNCH) $(CMD) archlinux $(VOL_TAB)

.PHONY: kalilinux
kalilinux:
	$(LAUNCH) $(CMD) kalilinux $(VOL_TAB)
