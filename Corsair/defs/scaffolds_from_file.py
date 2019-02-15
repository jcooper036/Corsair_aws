#!/usr/bin/env python3

import Corsair as cor
import os

def scaffolds_from_file(ctl, iso_name):
    """
    Input: control object, isoform name
    Operation: Loads blast scaffolds from a pre-computed blast dictionary.
    Output: saves modified isoform file 
    """

    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## set the file path
    scaffold_file = ctl.scaffold_path + iso.name + '_scaffolds.txt'

    ## grab the scaffolds from file. in format gene:species,header|scaffold|
    with open(scaffold_file, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            if line:
                line = line.split(':')[1].split(',')
                iso.add_scaffold(line[0], line[1].split('|')[1])
    
    ## save the isoform object
    cor.save_isoform(ctl, iso)