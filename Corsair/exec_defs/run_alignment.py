#!/usr/bin/env python3

import Corsair as cor
import os

def run_alignment(ctl, iso_name):
    """
    Input: control object, isoform name, aligner name
    Output: Alignment file in isoform folder
    """

    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## make sure that the gene has enough sequecnes
    if iso.blast_prot:
        if not len(list(iso.blast_prot.keys())) > 1:
            print('WARNING: Alignment did not run - not enough sequences to align')
            return None
    else:
        print('WARNING: Alignment did not run - blast sequences were not translated')
        return None

    ## loop over the commands for the different aligners
    for aligner in ['clustal', 'tcoffee', 'muscle']:

        ## specifiy the input and output file names
        infile = ctl.project_path + 'temp/' + iso.name + '_' + aligner + '.fasta'
        outfile = iso.alignment_file(ctl, aligner)

        ## make the file
        cor.write_fasta(infile, iso.blast_prot, list(iso.blast_prot.keys()))

        ## different commands based on aligner
        if aligner == 'clustal':
            command = ctl.mod_path + 'Corsair/bin/clustal-omega/1.2.1/bin/clustalo -i ' + infile +' -o ' + outfile + ' --force'
        if aligner == 'tcoffee':
            command = ctl.mod_path + 'Corsair/bin/t-coffee/10.00.r1613/bin/t_coffee ' + infile + ' -outfile ' + outfile + ' -multi_core -quiet -output=fasta'
        if aligner == 'muscle':
            command = ctl.mod_path + 'Corsair/bin/muscle/3.8.1551/bin/muscle -quiet -in ' + infile + ' -out ' + outfile
        
        cor.shell(command)
        print('Sequences for ' + iso.name + ' aligned with ' + aligner + '.')

        ## cleans up a file that is sometimes made, but useless
        try:
            os.remove(os.getcwd() + '/' + iso + '_coff.dnd')
        except:
            pass

        ## load the alignment as a dictionary into the isoform object
        iso.alignment[aligner] = cor.read_fasta(outfile)
        
        ## save the isoform object
        cor.save_isoform(ctl, iso)

