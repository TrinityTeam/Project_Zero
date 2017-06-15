#!/usr/bin/env python3

import sys
import os
import subprocess
import shlex

class Context: pass
context = Context()
context.projectRoot = os.path.abspath(".")
context.buildDir = os.path.abspath("bin")
context.cmakeOptions = ""
context.makeOptions = ""


def setCMakeOptions(args_iter, context):
    context.cmakeOptions = next(args_iter)
    print(context.cmakeOptions)

def setMakeOptions(args_iter, context):
    context.makeOptions = next(args_iter)

def setBuildDir(args_iter, context):
    context.buildDir = os.path.abspath(next(args_iter))

def printHelp():
    print("Options:\n\
           -c --cmake-options OPTIONS\tSet CMake build options\n\
           -m --make-options OPTIONS\tSet Make build options\n\
           -b --bin-dir DIR\tSet output directory\n")

commands = {
    "-c": setCMakeOptions, "--cmake-options": setCMakeOptions,
    "-m": setMakeOptions, "--make-options": setMakeOptions,
    "-b": setBuildDir, "--build-dir": setBuildDir,
    "-h": printHelp, "--help": printHelp
}

current = iter(sys.argv)
next(current)
try:
    while True:
        arg = next(current)
        if arg in commands:
            commands[arg](current, context)
        else:
            print("Invalid argument: ", arg)

except StopIteration:
    pass

print(context.cmakeOptions)


if not os.path.exists(context.buildDir):
    os.mkdir(context.buildDir)

os.chdir(context.buildDir)
print(shlex.split(context.cmakeOptions))
result = subprocess.run(["cmake"] + shlex.split(context.cmakeOptions) + [context.projectRoot+"/src/"])
if result.returncode != 0:
    exit(1)

result = subprocess.run(["make"] + shlex.split(context.makeOptions))
if result.returncode != 0:
    exit(1)

print("Building is complete")
