#!/usr/bin/env python3

import Corsair as cor
import os
import pickle

def initialize_isoforms(ctl):
    """
    input : control object (ctl)
    output : dictionary of isoform objects
    """
    isoforms = {}

    ## load the list of reference CDS sequences
    ref_CDS_seqs = cor.read_fasta(ctl.ref_cds)

    ## check that each isoform is in the reference CDS sequences
    not_there = []
    for iso in ctl.gene_list:
        
        ## if it is there, init the Isoform class and give it the reference sequence
        if iso in ref_CDS_seqs:
            isoforms[iso] = cor.Isoform(iso)
            isoforms[iso].ref_nt(ref_CDS_seqs[iso])
            isoforms[iso].ref_aa(cor.translate(isoforms[iso].ref_nt))
            if not os.path.isdir(ctl.project_path + 'genes/' + iso):
                os.mkdir(ctl.project_path + 'genes/' + iso)
            

        ## if not, add it to the list of problems
        else:
            not_there.append(iso)
    
    ## if problems, tell the user
    if len(not_there) > 0:
        print("WARNING: Some or all genes did not match an entry in the reference CDS file. The following genes need attention:")
        for gene in not_there:
            print('\t' + str(gene))

    return isoforms