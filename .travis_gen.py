#!/usr/bin/python3

## This is a python script file to generate a .travis.yml file according to some contents.
## To update the .travis.yml file, you just have to run python3 .travis_gen.py > .travis.yml

LANG = "C"
DIST = "xenial"
COMPILER = "gcc"

J_BASE = "Base"
J_TEST = "Test"
JOBS = [J_BASE, J_TEST]

# There are 2 stages,
#   - Base stage tests if the .travis.yml file is consistent to this script and if the project compile
#   - Test stage runs the programms on examples on several Linux Distributions

BASE_TASKS = [
    (J_BASE, "verifying travis.yml file", ["python3 .travis_gen.py > expected.out", "diff .travis.yml expected.out"]),
    (J_BASE, "compile woody woodpacker", ["make"]),
]

TEST_DISTRIBS = ["ubuntu", "debian", "fedora", "archlinux", "kalilinux"]

TEST_TASKS = []

def build_test_task(distrib):
	return ((J_TEST, "Testing on " + distrib, ["make -f test.mk " + distrib]))

for distrib in TEST_DISTRIBS:
	TEST_TASKS.append(build_test_task(distrib))

TASKS = BASE_TASKS + TEST_TASKS

def print_travis_config():
    def print_header():
        print("language:", LANG)
        print("dist:", DIST)
        print("compiler:", COMPILER)
        print("git:")
        print("  depth: false")
        print("  gitsubmodules: false")
        print()
        print("stages:")
        for job in JOBS:
            print("  -", job)
        print()

    def print_task(task):
        (stage, name, cmds) = task
        print("    - name:", name)
        print("      stage:", stage)
        print("      script:")
        for cmd in cmds:
            print("        -", cmd)

    print_header()
    print("matrix:")
    print("  include:")
    for task in TASKS:
        print_task(task)


def main():
    print_travis_config()


if __name__ == "__main__":
    main()
