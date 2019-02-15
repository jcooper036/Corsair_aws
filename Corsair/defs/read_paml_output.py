#!/usr/bin/env python3

import Corsair as cor
import os

def read_paml_output(ctl, iso_name):
    """
    Input: control object, iso name, aligner name
    Output: PAML results file for that aligner, updated isoform object
    """    
    
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## this dictionary contains a file path as the value, otherwise, contains false
    for aligner in iso.paml_output_files:
        if iso.paml_output_files[aligner]:
            if os.path.isfile(iso.paml_output_files[aligner]):
                iso = cor.read_paml_file(iso.paml_output_files[aligner], iso)

    ## calculate p-values - This has to go here because it needs to to go before M8a
    iso = cor.paml_pvalues(iso)

    ## save the isoform object
    cor.save_isoform(ctl, iso)