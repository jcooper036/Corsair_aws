#!/usr/bin/env python3

import Corsair as cor
from Bio import SeqIO, Phylo
from io import StringIO
import os

def build_tree(ctl, iso_name):
    """
    Input: control object, isoform name
    Output: modifies the isoform save file to include the exonerate result
    """
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## check to make sure that the CDS file exists 
    if not os.path.isfile(iso.CDS_file(ctl)):
        print("WARNING: There was no CDS file for {} so the tree could not be built".format(iso.name))
        return None

    ## load in the sequences
    cds = SeqIO.to_dict(SeqIO.parse(iso.CDS_file(ctl),'fasta'))

    #works for all groups, dependent on the clade/genomes combination
    handle = StringIO(ctl.tree) # read the string as a file
    tree = Phylo.read(handle,'newick') # loads tree

    ## remove all the species that did not have good sequences
    for species in ctl.species:
        if species not in iso.good_species:
            tree.prune(species)
    
    ## write the tree file
    temp_tree = ctl.project_path + 'temp/' + iso.name + '_tree.txt'
    Phylo.write(tree, temp_tree, 'newick')

    ## if there are enough species, then write it to the iso files and remove the branch lengths
    if len(iso.good_species) >= ctl.min_species:
        with open (temp_tree,'r') as infile, open(iso.tree_file(ctl),'w') as outfile:
            outfile.write(infile.read().replace(':0.00000',''))
        print('Tree for ' + iso.name +': built.')
    else:
        print('WARNING: Not enough species to analyze {}: Only found sequences for {}/{} required species'.format(iso.name, str(len(iso.good_species)), str(ctl.min_species)))
        with open(iso.results_file(ctl),'a') as f:
            f.write('\n' + str(iso.name) + '\tNot enough species for PAML: Only found ' + str(len(iso.good_species)) + ' species')
    
    ## remove the temp file
    os.remove(temp_tree) #removes temp file    

    ## save the isoform object
    cor.save_isoform(ctl, iso)
