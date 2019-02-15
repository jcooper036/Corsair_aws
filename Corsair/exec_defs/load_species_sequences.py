#!/usr/bin/env python3

import Corsair as cor

def load_species_sequences(ctl, iso_name):
    """
    Input: control object
    Output: updated isoform save file with the species sequences loaded in
    """

    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## load in a sequence
    blast_sequences = {}
    for species in ctl.species:
        blast_sequences[species] = []
        exonerate_file = iso.iso_files(ctl) + species + '.txt'
        with open(exonerate_file, 'r') as f:
            copy = False
            for line in f.readlines():
                line = line.strip()
                
                ## when to read the line
                if line == 'forcebeams':
                    copy = True
                elif line == '-- completed exonerate analysis':
                    copy = False
                elif line == 'C4 Alignment:':
                    copy = False

                ## what to do with the line if copy
                if copy:
                    if '>' not in line and 'forcebeams' not in line:
                        blast_sequences[species].append(line)
    
    ## these were lists, so merge those lists together
    for species in blast_sequences:
        blast_sequences[species] = ''.join(blast_sequences[species])
                
    ## check for the length requirement. This scales a little bit based on size - not much
    if len(iso.ref_nt) <= 2400:
        percent_req = (len(iso.ref_nt) / 40000) + (ctl.align_thresh - 0.05)
    elif len(iso.ref_nt) > 2400:
        percent_req = ctl.align_thresh
    
    ## define a min and max length that the sequence can be
    differential = 1-percent_req
    max_length = (1+differential) * len(iso.ref_nt)
    min_length = (1-differential) * len(iso.ref_nt)

    ## add them if they are long enough
    temp = {}
    for species in blast_sequences:
        ## check that the length is appropriate
        if max_length >= len(blast_sequences[species]) >= min_length:
            ## check that the sequence is divisable by 3
            if len(blast_sequences[species]) % 3 == 0:
                temp[species] = blast_sequences[species]
    temp[ctl.ref_species] = iso.ref_nt

    ## add it to the isoform
    iso.blast_search(temp)
    
    ## translate them
    iso.blast_trans()

    ## get rid of any sequences that have stop codons in the middle
    iso.stop_codon_prune()

    ## now let the isoform know what species it can actually use
    iso.good_species = list(iso.blast_dic.keys())

    ## in case all the sequences got deleted
    if not iso.good_species:
        print("ERROR: All sequences for {} contained stop codons".format(iso.name))
        return None

    ## write a CDS outfile. needed for tree building. Done this way so that the reference
    ## species will be the first
    order = [ctl.ref_species]
    for species in iso.good_species:
        if species != ctl.ref_species:
            order.append(species)
    
    cor.write_fasta(iso.CDS_file(ctl), iso.blast_dic, order)

    ## save the isoform object
    cor.save_isoform(ctl, iso)
