import os, inspect, subprocess

projectRoot = os.path.dirname(os.path.abspath(inspect.stack()[0][1]))

os.chdir(projectRoot)
if subprocess.run(["./build.py"]).returncode != 0:
    exit(1)
os.chdir("bin")
subprocess.run(["./GameClient"])
