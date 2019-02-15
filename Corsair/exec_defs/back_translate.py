#!/usr/bin/env python3

import Corsair as cor
from copy import deepcopy

def back_translate(ctl, iso_name):
    """
    Input: control object, isoform name, aligner name
    Output: modifies the iso object to contain a dictionary of the back translated CDS sequence for PAML AND a .paml file for the alignment
    """
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)
    
    ## check to make sure everything will work
    if not iso.trimmed:
        print("WARNING: Back translation did not happen. There were no trimmed sequences")
        return None
    
    aa_alignment = iso.trimmed

    ## generate a list of all the indexed positions that do not have a *, -, or X in any sequence
    good_indexes = []
    for i in range(len(aa_alignment[ctl.ref_species])):
        if not any(aa_alignment[nkey][i] == "*" or aa_alignment[nkey][i] == "X" or aa_alignment[nkey][i] == "-" for nkey in aa_alignment):
            good_indexes.append(i)
    
    ## use those positions to build the new min sequences
    minaa = {}
    for species in aa_alignment:
        condensed_sequence = ''
        for i in good_indexes:
            condensed_sequence += aa_alignment[species][i]
        minaa[species] = condensed_sequence

    ## now trasnlate the CDS sequence step by step, see if it matches the nucleotide. Because of
    ## how positions were removed, the correct codons should appear in order once deleted
    ## codons are skipped
    nuc_input = deepcopy(iso.blast_dic)
    for species in nuc_input:
        k = 0
        while k < len(minaa[species]):
            if not minaa[species][k] == cor.translate(nuc_input[species][(k*3):((k*3)+3)]):
                nuc_input[species] = nuc_input[species][:(k*3)] + nuc_input[species][(k*3)+3:]
            else:
                k += 1
        else:
            nuc_input[species] = nuc_input[species][:(k*3)]

    ## give it to the isoform
    iso.backtrans = nuc_input

    ## write the .paml file
    order = [ctl.ref_species]
    for species in iso.good_species:
        if species != ctl.ref_species:
            order.append(species)
    with open(iso.paml_file(ctl), 'w') as f:
        f.write('\t' + str(len(nuc_input.keys())) + '\t' + str(len(nuc_input[ctl.ref_species])) + '\n') ## changed to 'clade' variable
        for key in order:
            f.write(str(key) + '\n')
            f.write(str(nuc_input[key]) + '\n')
    
    ## save the isoform object
    cor.save_isoform(ctl, iso)
