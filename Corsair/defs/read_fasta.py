#!/usr/bin/env python3

def read_fasta(file):
    """
    Input: fasta file
    Output: dictionary with header:sequence
    """
    wholefile = {}
    with open(file,'r') as f:
        for line in f.readlines():
            if ">" in line:
                keyname = [x.strip() for x in line]
                keyname = ''.join(keyname)
                keyname = keyname.split('>')[1]
                wholefile[keyname] = []
            elif '>' not in line:
                line = [x.strip() for x in line]
                line = ''.join(line)
                wholefile[keyname].append(line)
    for key in wholefile:
        wholefile[key] = ''.join(wholefile[key])

    return wholefile