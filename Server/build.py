#!/usr/bin/env python3

import sys
import os
import subprocess
import shlex

projectRoot = os.path.abspath(".")
buildDir = os.path.abspath("bin")
cmakeOptions = ""
makeOptions = ""


def setCMakeOptions(args_iter):
    cmakeOptions = next(args_iter)

def setMakeOptions(args_iter):
    makeOptions = next(args_iter)

def setBuildDir(args_iter):
    buildDir = os.path.abspath(next(args_iter))

def printHelp():
    print("Options:\n\
           -c --cmake-options OPTIONS\tSet CMake build options\n\
           -m --make-options OPTIONS\tSet Make build options\n\
           -b --bin-dir DIR\tSet output directory\n")

commands = {
    "-c": setCMakeOptions, "--cmake-options": setCMakeOptions,
    "-m": setMakeOptions, "--make-options": setMakeOptions,
    "-b": setBuildDir, "--build-dir": setBuildDir,
    "-h": printHelp
}

current = iter(sys.argv)
next(current)
try:
    while True:
        arg = next(current)
        if arg in commands:
            commands[arg](current)
        else:
            print("Invalid argument: ", arg)

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
