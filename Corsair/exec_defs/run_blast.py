#!/usr/bin/env python3

import Corsair as cor
import os

def run_blast(ctl, iso_name):
    """
    Input: ctl file, isoform name
    Output: blast scaffold data in the isform file
    """

    ## load the iso object
    iso = cor.load_isoform(ctl, iso_name)

    ## check for what BLAST needs
    missing = []
    for species in ctl.genome_paths:
        if not ctl.genome_paths[species]:
            missing.append(species)
    if missing:
        print("ERROR: Could not find genomes for {}, aborting BLAST".format(missing))
        return None

    print('Running tBLASTn for ' + iso.name)

    ## check that the isoform has the appropriate data
    if not type(iso.ref_nt) == str:
        print("ERROR: Isoform object was not prepared for BLAST - no reference protein sequence")
        return None
    
    ## check if the BLAST database has been made, make it if not
    for species in ctl.genome_paths:
        genome = ctl.genome_paths[species]
        if not os.path.exists(genome + '.nhr'):
            print("UPDATE: making BLAST database for " + genome)
            command = 'makeblastdb -in ' + genome + ' -parse_seqids -dbtype nucl'
            cor.shell(command)
        if not os.path.exists(genome + '.fai'):
            print("UPDATE: making faidx database for " + genome)
            command = 'samtools faidx ' + genome
            cor.shell(command)

    ## run blast - output is a scaffold file in the gene folder. iso object knows them too
    for species in ctl.genome_paths:
        command = 'tblastn -outfmt "6" -query <(echo ' + iso.ref_aa + ') -db ' + ctl.genome_paths[species] + ' -max_target_seqs 1| head -n 1'
        scaffold = str(cor.shell(command)).split('\t')[1]
        iso.add_scaffold(species, scaffold)

    ## save the iso object
    cor.save_isoform(ctl, iso)