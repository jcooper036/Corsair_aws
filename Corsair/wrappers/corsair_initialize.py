#!/usr/bin/env python3

import Corsair as cor

def corsair_initialize(ctl):
    """
    Input: ctl file
    Output: File stucture for running corsair, including pkl files for each gene.
    Only needs to be run if no data is currently present.
    """
    
    ## initialize all the genes in the list and save. This clears all data for them.
    isoforms = cor.initialize_isoforms(ctl)
    for iso in isoforms:
        cor.save_isoform(ctl, isoforms[iso])
