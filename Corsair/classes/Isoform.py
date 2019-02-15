#!/usr/bin/env python3

import os
import pickle
import Corsair as cor

class Isoform(object):
    """Holds information about an isoform"""

    #################
    ## these are used to Initialize and operate on the isoform class
    #################

    def __init__(self, name):
        """constructor function"""
        self.name = name
        self.ensembl = False
        self.blast_prot = {}
        self.alignment = {} # protein alignment with all good speices
        self.condensed_alignment = {} # protein alignment for each aligner with -, X, * removed
        self.trimmed = {} # protein alignment (species:seq) trimmed to min agreement between all aligners
        self.backtrans = {} # back translanted CDS sequecnes for each species with indels removed
        self.BEB_sites = {} # aligner : list of BEB sites
        self.BEB_sites['same_sites'] = [] # List of sites that are common between all aligners
        self.ref_min_aa = {} # the minimum amino acid sequence of the reference after all indels compared with other species are removed
        self.scaffolds = {} # species:scaffold, filled after blast
        self.good_species = [] # eventually filled with the species that have good sequences
        self.mask = False

        # will hold the results from PAML
        self.paml_results = {
            'logLvals' : {'M7' : False, 'M8' : False, 'M8a' : False},
            '2delta' : {'M7M8' : False, 'M8M8a' : False},
            'pval' : {'M7M8' : False, 'M8M8a' : False},
            'beb_sites_raw' : {},
            'beb_total_sites' : {},
            'beb_hit_sites' : {}
        }
        
        ## tree lengths from PAML
        self.tree_length = {'M7' : False, 'M8' : False}
        
        ## dN/dS stats
        self.dnds = {
            'av_dnds' : False,
            'max_ds' : False,
            'list_dnds' : [],
            'tuple_dnds' : [],
            'list_ds' : [],
            'list_dn' : [],
            'recorded' : False
        }

        # will hold the results paths for each run of PAML. keys are model comparisons
        self.paml_output_files = {'M7M8' : False, 'M8M8a' : False}


    #################
    ## defs for explicity adding varibles
    ## mostly to increase readability
    #################

    def ref_nt(self, ref_nt):
        """Adds the reference nucleotide string"""
        self.ref_nt = ref_nt

    def ref_aa(self, ref_aa):
        """Adds the reference amino acid string"""
        self.ref_aa = ref_aa

    def add_scaffold(self, species, scaffold):
        """Add a scaffold"""
        self.scaffolds[species] = scaffold

    #################
    ## these are some property functions to return common file paths
    ## they help make the handling of everything else much more readable
    #################

    def iso_files(self, ctl):
        """Input : control object, Output, path to files folder for isoform"""
        return ctl.project_path + 'genes/' + self.name + '/' + self.name + '_files/'

    def protein_file(self, ctl):
        ## returns the protein file path
        return self.iso_files(ctl) + self.name + '_prot.txt'

    def CDS_file(self, ctl):
        ## returns the cds_file path
        return self.iso_files(ctl) + self.name + '_CDS.txt'

    def alignment_file(self, ctl, algnr):
        """Takes control object and alinger name, returns a file path"""
        try:
            return self.iso_files(ctl) + self.name + '_' + algnr + '.fasta'
        except:
            print('Need to specify an aligner')

    def paml_file(self, ctl):
        ## returns the paml alignment file path
        try:
            return self.iso_files(ctl) + self.name + '.paml'
        except:
            print('Need to specify and aligner')

    def tree_file(self, ctl):
        ## returns the tree file path
        return self.iso_files(ctl) + self.name + '_tree.txt'
    
    def results_file(self, ctl):
        try:
            return ctl.project_path + 'genes/' + self.name + '/' + self.name + '_results.txt'
        except:
            print('Could not properly specifiy results file')
    
    def paml_control_file(self, ctl):
        return self.iso_files(ctl)  + 'codeml.ctl'

    #################
    ## these are used in the processing of the data
    #################

    def blast_search(self, blast_dic):
        """Adds in a dictionary of species:nt_sequecnes from blast and exonerate"""
        self.blast_dic = blast_dic

    def blast_trans(self):
        """Translates self.blast_dic into protein sequences, stored in self.blast_prot"""
        try:
            for key in self.blast_dic:
                self.blast_prot[key] = cor.translate(self.blast_dic[key])
        except:
            print("ERROR: There is no blast dictionary")
    
    def stop_codon_prune(self):
        """Removes sequences that have stop codons in the middle of the sequence"""
        remove = []
        for species in self.blast_prot:
            test = self.blast_prot[species].upper()[:-1]
            if 'X' in test:
                remove.append(species)
        if len(remove) > 0:
            for species in remove:
                self.blast_dic.pop(species)
                self.blast_prot.pop(species)
