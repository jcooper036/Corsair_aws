#!/usr/bin/env python3

import subprocess

def shell(command):
    return subprocess.check_output(command, shell=True, executable='/bin/bash').decode('utf-8').strip()
