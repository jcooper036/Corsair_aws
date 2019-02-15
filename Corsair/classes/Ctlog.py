#!/usr/bin/env python3
import glob
import sys

class Ctlog():
    """This class is the equivalent of a control file, holds all the parameters for
       running the program"""
    
    def __init__(self, file):
        """constructor function"""
        self.file = file
        self.load_params()

    def __repr__(self):
        """Print function for the class"""
        # ugly command incoming
        return "Project:{}, Reference CDS: {}, Genome Directory:{} Tree:{}, Reference Species: {}, Min species:{}, Alignment threshold:{}".format(self.project_path, self.ref_cds, self.genome_path, self.tree, self.ref_species, self.min_species, self.align_thresh)


    def load_params(self):
        """loads in the parameters from it's ctl file"""

        with open(self.file, 'r') as f:
            for line in f.readlines():
                line = line.strip()
                if 'corsair_directory:' in line:
                    self.mod_path = line.split(':')[1]
                    self.mod_path = self.add_slash(self.mod_path)
                if 'project_directory:' in line:
                    self.project_path = line.split(':')[1]
                    self.project_path = self.add_slash(self.project_path)
                if 'reference_CDS:' in line:
                    self.ref_cds = line.split(':')[1]
                if 'genome_directory:' in line:
                    self.genome_path = line.split(':')[1]
                    self.genome_path = self.add_slash(self.genome_path)
                if 'tree:' in line:
                    self.tree = line.split(':')[1]
                if 'ref_spec:' in line:
                    self.ref_species = line.split(':')[1]
                if 'minimum_species:' in line:
                    try:
                        self.min_species = int(line.split(':')[1])
                    except:
                        self.min_species = 3
                    if self.min_species < 3:
                        self.min_species = 3
                        print("There cannot be less than 3 species for this analysis. The minimum species count has been set to 3")
                if "alignment_threshold:" in line:
                    try:
                        self.align_thresh = float(line.split(':')[1])
                    except:
                        self.align_thresh = 0.95
                    if self.align_thresh > 1:
                        print("The minimum alignment threshold cannot be greater than 1. It has been set to 1.")
                        self.align_thresh = 1
                    elif self.align_thresh < 0.7:
                        print("The minimum alignment threshold cannot be less than 0.7. It has been set to 0.7.")
                        self.align_thresh = 0.7
                if "gene_list:" in line:
                    self.secret_gene_list = []
                    self.gene_file = line.split(':')[1]
                    with open(self.gene_file, 'r') as f:
                        for line in f.readlines():
                            line = line.strip()
                            if line:
                                self.secret_gene_list.append(line)
                if "BEB_threshold:" in line:
                    try:
                        self.beb_threshold = float(line.split(':')[1])
                    except:
                        self.beb_threshold = 0.95
                
                if "blast_scaffolds:" in line:
                    try:
                        self.scaffold_path = str(line.split(':')[1])
                        self.scaffold_path = self.add_slash(self.scaffold_path)
                    except:
                        pass
                           
        self.species_list(self.tree)
        self.find_genome_paths()

    def add_slash(self, string):
        """looks for '/' on the end of string, add it if not there"""
        if string[-1] != '/':
            string += '/'
        return string
    
    def species_list(self, tree):
        """Builds a list of species from the species listed in the tree"""
        self.species = self.tree.split(',')
        ## replace all the "(", ")", and ";" to leave only species IDs
        self.species = [x.replace('(','').replace(')','').replace(';','') for x in self.species]
        temp = []
        for species in self.species:
            if species != self.ref_species:
                temp.append(species)
        self.species = temp

    def find_genome_paths(self):
        """Looks in the genome folder, gets the exact file paths to the different genomes"""
        self.genome_paths = {}
        for genome in self.species:
            gen = False
            for name in glob.glob(self.genome_path + genome + '_*.fasta'):
                gen = name
            if not gen:
                print('ERROR: Genome files could not be found. They must contain the species code followed by an underscore, and end in .fasta')
            self.genome_paths[genome] = gen
    
    def load_gene_list(self):
        """Actaully uses the gene list. This is here in case the gene list is set by other means"""
        self.gene_list = self.secret_gene_list