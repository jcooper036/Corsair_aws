#!/usr/bin/env python3

import Corsair as cor

def align_and_paml(ctl, iso):
    """
    Input: control object, isoform name
    Output: results in the isoform folder in the project directory
    
    Temporary def, for practicing doing everything. Need to keep in mind that variable 
    passing needs to be such that everything can be run by itself, and not kill memory,
    and be divided onto as many CPUS as possible, and it needs to be able to quit and
    not lose everything.
    """
    
    ## align
    cor.run_alignment(ctl, iso)
    
    ## trim to minimum alignment
    cor.trim_sequences(ctl, iso)

    ## back translate
    cor.back_translate(ctl, iso)

    ## build the tree
    cor.build_tree(ctl, iso)

    ## run PAML
    cor.run_paml_M7M8(ctl, iso)

    ## read the output
    cor.read_paml_output(ctl, iso)

    ## run M8a
    cor.run_paml_M8M8a(ctl, iso)