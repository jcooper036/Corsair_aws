#!/usr/bin/env python3

import Corsair as cor

def align_and_m7m8(ctl, iso, aligner):
    """
    Input: control object, isoform name
    Output: PAML output results in the isoform folder in the project directory
    """

    ## blast
    cor.run_blast(ctl, iso)

    ## exonerate on the scaffolds
    cor.run_exonerate(ctl, iso)
    cor.load_species_sequences(ctl, iso)
    
    ## align
    cor.run_alignment(ctl, iso, aligner)
    
    ## back translate
    cor.back_translate(ctl, iso, aligner)

    ## build the tree
    cor.build_tree(ctl, iso)

    ## run PAML
    cor.run_paml_M7M8(ctl, iso, aligner)

def run_m8m8a(ctl, iso, aligner):
    
    ## figure out which aligner to use
    alinger = cor.highest_pvalue(ctl, iso)

    ## run PAML
    cor.run_paml_M8M8a(ctl, iso, aligner)