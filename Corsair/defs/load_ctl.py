#!/usr/bin/env python3
import Corsair as cor
import os
import fnmatch

def load_ctl(file):
    """
    Loads a control file, returns the ctl object. 
    Makes sure that all the directories exist as well
    """
    ## load the ctl object
    ctl = cor.Ctlog(file)
    
    ## Check that the project directory exists. if not, make it
    print('Checking for project directory')
    if not os.path.isdir(ctl.project_path):
        print("Making project directory")
        os.makedirs(ctl.project_path)

    ## Check that there is a genome for each species that is claimed in the tree. Raise an error if not.
    print('Checking for genome files')
    if os.path.isdir(ctl.genome_path):
        cleared = {}
        for species in ctl.species:
            cleared[species] = False
            for file in os.listdir(ctl.genome_path):
                if fnmatch.fnmatch(file, (species + '_*')):
                    cleared[species] = True
        if not all(cleared[x] for x in cleared):
            print("ERROR: Could not link the following species genomes:")
            for speices in cleared:
                if not cleared[speices]:
                    print('\t' + speices)
            return "Aborting"
    else:
        print("ERROR: Genome directory not found.")
    
    ## Check that the reference CDS file exists. Raise and error if not
    print('Checking for the reference CDS fasta file')
    if not os.path.exists(ctl.ref_cds):
        print("ERROR: Could not find the reference CDS fasta file")
        return "Aborting"
    
    print('Checking for the gene list')
    if not os.path.exists(ctl.gene_file):
        print("ERROR: Could not find the gene list file")
        return "Aborting"

    ## makes a folder for the genes if that doesn't exit
    if not os.path.isdir(ctl.project_path + 'genes/'):
        os.mkdir(ctl.project_path + 'genes/')

    return ctl