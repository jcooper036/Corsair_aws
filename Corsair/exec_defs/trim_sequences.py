#!/usr/bin/env python3

import Corsair as cor
import os

def trim_sequences(ctl, iso_name):
    """
    Input: control object, isoform name
    Operation: Trims the alignments down to minimum amino acid alignment, no gaps
    Output: saves modified isoform file 
    """

    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## make sure the alignment is there
    if not iso.alignment:
        print('WARNING: Trimming did not take place - no sequence alignmnets')
        return None

    ## remove all the indels from each sequence
    for aligner in ['clustal', 'tcoffee', 'muscle']:
        iso.condensed_alignment[aligner] = min_aa_seq(ctl, iso.alignment[aligner])

    ## now, we need to line those all up against the reference sequence
    iso.trimming = {
        'ref' : iso.ref_aa,
        'clustal' : {},
        'tcoffee' : {},
        'muscle' : {}
    }
    aligner_idx = {
        'clustal' : 0,
        'tcoffee' : 0,
        'muscle' : 0
    }
    mask_counter = {
        'clustal' : 0,
        'tcoffee' : 0,
        'muscle' : 0      
    }
    seq_mask = {
        'clustal' : [],
        'tcoffee' : [],
        'muscle' : []        
    }

    ## make some blank variables to add to
    for aligner in ['clustal', 'tcoffee', 'muscle']:
        for species in iso.condensed_alignment[aligner]:
            iso.trimming[aligner][species] = ''

    ## lign up all the alignments with the reference, build a mask that tells where to add -
    for aminoacid in iso.trimming['ref']:
        for aligner in ['clustal', 'tcoffee', 'muscle']:
            miss = False
            ## check to see if in range
            if aligner_idx[aligner] < len(iso.condensed_alignment[aligner][ctl.ref_species]):
                test_aa = iso.condensed_alignment[aligner][ctl.ref_species][aligner_idx[aligner]]
            else:
                test_aa = ''
                miss = True

            ## check to see if the amino acids are the same
            if test_aa == aminoacid:
                mask_counter[aligner] += 1
                aligner_idx[aligner] += 1
            else:
                miss = True
            
            ## if either missed, add a -
            if miss:
                if mask_counter[aligner] > 0:
                    seq_mask[aligner].append(mask_counter[aligner])
                seq_mask[aligner].append('-')
                mask_counter[aligner] = 0

    ## now we need to apply that mask to each sequence
    for aligner in ['clustal', 'tcoffee', 'muscle']:
        for species in iso.condensed_alignment[aligner]:
            idx = 0
            for mask in seq_mask[aligner]:
                if mask != '-':
                    count = mask
                    while count > 0:
                        iso.trimming[aligner][species] += iso.condensed_alignment[aligner][species][idx]
                        count -= 1
                        idx += 1
                else:
                    iso.trimming[aligner][species] += '-'
    
    ## make a set of the indexes that we want to get rid of
    iso.mask = set()
    
    for idx in range(len(iso.trimming['ref'])):
        if any(iso.trimming[aligner][ctl.ref_species][idx] == '-' for aligner in ['clustal', 'tcoffee', 'muscle']):
            iso.mask.add(idx)

    ## add +1 and -1 site for every site in the mask
    temp =  set()
    for site in iso.mask:
        temp.add(site)
        if (site - 1) >= 0:
            temp.add(site - 1) # only add things that are possible
        temp.add(site + 1)
    iso.mask = temp

    ## find the insertion positions as compared to the ref, add the flanking positions to the mask
    for aligner in ['clustal', 'tcoffee', 'muscle']:
        count = 1
        for pos in iso.alignment[aligner][ctl.ref_species]:
            if pos == '-':
                if (count-1) >= 0:
                    iso.mask.add(count-1)
                iso.mask.add(count)
            else:
                count += 1

    ## apply the mask to each species, doesn't matter which alinger we use
    for species in iso.condensed_alignment['clustal']:
        iso.trimmed[species] = ''
        for idx in range(len(iso.condensed_alignment['clustal'][species])):
            if idx not in iso.mask:
                iso.trimmed[species] += iso.trimming['clustal'][species][idx]

    ## save the isoform object
    cor.save_isoform(ctl, iso)

def min_aa_seq(ctl, aa_alignment):
    """
    Input: amino acid alignment dictionary (species:sequence)
    Output: same dictionary structure, all indels and stops removed
    """
    minaa = {}

    ## generate a list of all the indexed positions that do not have a *, -, or X in any sequence
    good_indexes = []
    for i in range(len(aa_alignment[ctl.ref_species])):
        if not any(aa_alignment[nkey][i] == "*" or aa_alignment[nkey][i] == "X" or aa_alignment[nkey][i] == "-" for nkey in aa_alignment):
            good_indexes.append(i)

    ## use those positions to build the new min sequences
    for species in aa_alignment:
        condensed_sequence = ''
        for i in good_indexes:
            condensed_sequence += aa_alignment[species][i]
        minaa[species] = condensed_sequence

    return minaa