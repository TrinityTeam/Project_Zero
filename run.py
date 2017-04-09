#!/usr/bin/env python3

import sys
import os
import subprocess

os.system("./build.py")

dataDir = os.path.abspath("data")
binDir = os.path.abspath("bin")
executable = None

current = iter(sys.argv)
next(current)
try:
    while True:
        arg = next(current)
        if arg == "--data":
            dataDir = os.path.abspath(next(current))

        elif arg == "--client":
            binDir = os.path.abspath('bin/client')
            executable = "GameClient"

        elif arg == "--server":
            binDir = os.path.abspath('bin/server')
            executable = "GameServer"

        elif arg == "-h" or arg == "--help":
            print("Options:\n\
                  --server\tRun server\n\
                  --client\tRun client\n\
                  --data DIR\t Set data directory\n\
                  ")

except StopIteration:
    pass

os.chdir(dataDir)
result = subprocess.run([binDir+"/"+executable])
if result.returncode != 0:
    exit(1)
