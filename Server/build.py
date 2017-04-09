#!/usr/bin/env python3

import sys
import os
import subprocess
import shlex

projectRoot = os.path.abspath(".")
buildDir = os.path.abspath("bin")
cmakeOptions = ""
makeOptions = ""

current = iter(sys.argv)
next(current)
try:
    while True:
        arg = next(current)
        if arg == "-c" or arg == "--cmake-options":
            cmakeOptions = next(current)

        elif arg == "-m" or arg == "--make-options":
            makeOpions = next(current)

        elif arg == "-b" or arg == "--bin-dir":
            buildDir = os.path.abspath(next(current))

        elif arg == "-h" or arg == "--help":
            print("Options:\n\
                   -c --cmake-options OPTIONS\tSet CMake build options\n\
                   -m --make-options OPTIONS\tSet Make build options\n\
                   -b --bin-dir DIR\tSet output directory\n\
                   -d -data-dir DIR\t Set data directory\n")

except StopIteration:
    pass




if not os.path.exists(buildDir):
    os.mkdir(buildDir)

os.chdir(buildDir)
result = subprocess.run(["cmake"] + shlex.split(cmakeOptions) + [projectRoot+"/src/"])
if result.returncode != 0:
    exit(1)

result = subprocess.run(["make"] + shlex.split(makeOptions))
if result.returncode != 0:
    exit(1)

print("Building is complete")