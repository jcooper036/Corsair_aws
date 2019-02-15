#!/usr/bin/env python3

import os
import pickle
from scipy.stats import chi2

class Isoform(object):
    """Holds information about an isoform"""

    #################
    ## these are used to Initialize and operate on the isoform class
    #################

    def __init__(self, name):
        self.name = name
        self.alignment = {}
        self.backtrans = {}
        self.BEB_sites = {}
        self.BEB_sites['same_sites'] = []
        self.ref_min_aa = {}

    def rename(self, newname):
        ## renames the isoform
        self.name = newname

    def link_parent(self):
        ## used to link an isoform with a parent gene
        self.parent_gene = self.name.split('_')[0]

    def ref_nt(self, ref_nt):
        # nt_seq must be a string. also as is, this can't be over-written
        self.ref_nt = ref_nt

    def translate(self):
        # translates the nt_seq if there is one
        try:
            self.ref_aa = trans(self.ref_nt)
        except:
            print("ERROR: There is no nucleotide sequence for this gene")

    def scaffold_assignment(self, file1):
        with open(file1, 'rb') as input:
            scaffold_dic = pickle.load(input)
        self.scaffolds = scaffold_dic[self.parent_gene.replace('-a-','.')]

    #################
    ## these are some property functions to return common file paths
    ## they help make the handling of everything else much more readable
    #################

    def iso_files(self):
        ## returns the path to the files folder
        return self.name + '/' + self.name + '_files/'

    def CDS_file(self):
        ## returns the cds_file path
        return self.name + '/' + self.name + '_files/' + self.name + '_CDS.txt'

    def prot_file(self):
        ## returns the protein file path
        return self.name + '/' + self.name + '_files/' + self.name + '_prot.txt'

    def alignment_file(self, algnr):
        ## returns the file path with the specified alinger
        try:
            return self.name + '/' + self.name + '_files/' + self.name + '_' + algnr + '.fasta'
        except:
            print('Need to specify an aligner')

    def paml_file(self, algnr):
        ## returns the paml alignment file path
        try:
            return self.name + '/' + self.name + '_files/' + self.name + '_' + algnr + '.paml'
        except:
            print('Need to specify and aligner')

    def tree_file(self):
        ## returns the tree file path
        return self.name + '/' + self.name + '_files/' + self.name + '_tree.txt'

    def paml_output(self, algnr):
        ## returns the file path for the paml output file for a given aligner
        try:
            return self.name + '/' + self.name + '_files/' + self.name + '_' + algnr + '_PAML_out_full.txt'
        except:
            print('Need to specify and aligner')

    def p8ml_output(self, algnr):
        ## returns the file path for the paml output file for a given aligner
        try:
            return self.name + '/' + self.name + '_files/' + self.name + '_' + algnr + '_M8a_PAML_out_full.txt'
        except:
            print('Need to specify and aligner')

    def results_file(self):
        try:
            return self.name + '/results.txt'
        except:
            print('Could not properly specifiy results file')

    #################
    ## these are used in the processing of the data
    #################

    def blast_search(self, blast_dic):
        # reads in a dicitonary of species:sequence pairs
        self.blast_dic = blast_dic

    def blast_trans(self):
        # translates the blast dicitonary
        try:
            self.blast_prot = {}
            for key in self.blast_dic:
                self.blast_prot[key] = trans(self.blast_dic[key])
        except:
            print("ERROR: There is no blast dictionary")

    def load_alignment(self, aligner, file1):
        ## gives .aln property, which is a dictionary containing aligner names that are in turn dictionaries with alignments
        self.alignment[aligner] = {}
        self.alignment[aligner] = fasta_read(file1)

    def load_backtrans(self, aligner, bctrns):
        ## gives .backtrans property, which is a dictionary containing aligner names that are in turn dictionaries with alignments
        ## bctrns is a dictionary that contaisn the back-translation in nt form
        self.alignment[aligner] = {}
        self.alignment[aligner] = bctrns

    def spec_number_check(self,speccount): ##This makes sure that analysis isn't run if PAML file isn't there
        if len(self.blast_dic) >= speccount:
            return True
        else:
            return False

    def loglike_get(self):
        ## scans the results file for a log-likelihood values
        ## stores properties in a dictionary:
        ## llvals: dictionary of aligner_model : log-likelihood
        self.llvals = {}
        for algr in ('clus','coff','mus'):
            try:
                if os.path.exists(self.paml_output(algr)):
                    with open(self.paml_output(algr), 'r') as f:
                        flag = False
                        for line in f.readlines():

                            if 'Model' in line: ## determines the model
                                flag = True
                                line = [x.strip() for x in line]
                                line = ''.join(line)
                                line = line.split('Model')[1]
                                line = line.split(':')[0]
                                if line: # takes care of some blank lines that get returned
                                    model = algr + '_M' + line

                            if flag and 'lnL' in line: ## gets the log-likelihood value
                                line = [x.strip() for x in line]
                                line = ''.join(line)
                                line = line.split('):')[1]
                                lnl = line.split('+')[0]
                                self.llvals[model] = lnl
                                flag = False
                else:
                    if debug:
                        print('PAML output file for ' + algr + ' not detected.')
            except:
                print('Can not open paml file')

            if 'clus_M7_M8_p' not in self.llvals:
                self.llvals['clus_M7_M8_p'] = 37767



            if os.path.exists(self.p8ml_output(algr)):
                with open(self.p8ml_output(algr), 'r') as f:
                    for line in f.readlines():
                       if 'lnL' in line: ## gets the log-likelihood value
                            model = algr + '_M8a'
                            line = [x.strip() for x in line]
                            line = ''.join(line)
                            line = line.split('):')[1]
                            lnl = line.split('+')[0]
                            self.llvals[model] = lnl
                            flag = False

            ## calculates the 2Delta log-likelihood
            ## calculates a p-value

            M7 = algr + '_M7'
            M8 = algr + '_M8'
            M8a = algr + '_M8a'
            M7_M8_2del = algr + '_M7_M8_2del'
            M7_M8_p = algr + '_M7_M8_p'
            M8_M8a_2del = algr + '_M8_M8a_2del'
            M8_M8a_p = algr + '_M8_M8a_p'

            ## see if there is a M7-M8 comparison
            try:
                self.llvals[M7_M8_2del] = 2 * ( abs( float(self.llvals[M7]) - float(self.llvals[M8]) ))
                self.llvals[M7_M8_p] = chi2.sf ( self.llvals[M7_M8_2del] , 2 )
            except:
                pass #@ And a message here I think.

            ## see if there is a M8-M8a comparison
            try:
                self.llvals[M8_M8a_2del] = 2 * ( abs( float(self.llvals[M8]) - float(self.llvals[M8a]) ))
                self.llvals[M8_M8a_p] = chi2.sf ( self.llvals[M8_M8a_2del] , 1 )
            except:
                pass #@ Message about no significant p-values.

        ## determine the current highest p-value
        d = {}
        for algr in ('clus','mus','coff'):
            try:
                M7_M8_p = algr + '_M7_M8_p'
                d[algr] = self.llvals[M7_M8_p] #@ debug step could be to print these.
            except:
                pass

        # self.llvals['max_p'] = keywithmaxval(d)
        if d:
            self.llvals['max_p'] = max(d, key=d.get)
        else:
            pass

    def site_get(self, algnr):
        # gets the positions of the amino acids under selection in the origonal reference sequence
        # requires: self.llvals['max_p']
        # creates property: self.BEB_sites

        uncor_sites = []  ## this is the list of uncorrected BEB sites
        flag1=False
        flag2=False

        with open(self.paml_output(algnr),'r') as f:
            for line in f.readlines():
                if '+-' in line and not 'Pr(w>1)' in line:
                    line = line.split()
                    line[2] = line[2].replace('*', '')
                    if float(line[2]) > 0.90:
                        uncor_sites.append(line[0])
        if debug:
            print('Sites under selection, before correction (pp > 0.90) for ' + algnr + ': ' + str(uncor_sites))

        ## extracts the D.mel reduced sequence form the PAML input file
        flag1 = False
        count = 0
        red_seq = []
        with open(self.paml_file(algnr),'r') as f:
            for line in f.readlines():
                if clade in line:
                    flag1 = True
                if flag1 and count < 2:
                    line = [x.strip() for x in line]
                    line = ''.join(line)
                    red_seq.append(line)
                    count += 1

        ## two new properties that contain the reduced reference sequences
        self.ref_min_nt = {algnr : red_seq[1]}
        self.ref_min_aa[algnr] = trans(self.ref_min_nt[algnr])

        ## use UPPER CASE to denote the BEB amino acids
        indicies = [] ## since the index position will be sites - 1
        for i in uncor_sites:
            indicies.append(int(i) - 1)
        self.ref_min_aa[algnr] = ("".join(c.upper() if i in indicies else c for i, c in enumerate(self.ref_min_aa[algnr].lower())))

        if debug:
            print(self.ref_min_aa[algnr])
            print(self.ref_aa)
            print('\n')

        ## iterate through the length of the main sequence. Check if the two are
        ## equal. If not, add a '-' to the reduced sequence, and check the next
        ## position. The result is that self.ref_min_aa has dashes and BEB sites
        ## in UPPER CASE, and is the same length as teh ref_aa sequence.
        for i in range(0,len(self.ref_aa)):
            try:
                if debug:
                    print(str(i) + ' - ' + self.ref_min_aa[i] + ' , ' + self.ref_aa[i])
                if self.ref_min_aa[algnr][i].lower() != self.ref_aa[i].lower():
                    if i == 0:
                        self.ref_min_aa[algnr] = '-' + self.ref_min_aa[algnr]
                    else:
                        self.ref_min_aa[algnr] = self.ref_min_aa[algnr][:i] + '-' + self.ref_min_aa[algnr][i:]
            except:
                pass

        # get the list of sites that are in UPPER CASE
        self.BEB_sites[algnr] = []
        for i, c in enumerate(self.ref_min_aa[algnr]):
            if c.isupper():
                self.BEB_sites[algnr].append(i+1)


        if debug:
            print ('Sites under selection (pp > 0.90) for ' + algnr + ': ' + str(self.BEB_sites[algnr]))

    def site_analysis(self):
        ## reduces to the common sites for all aligners, and generates some other data
        ## makes a list called self.BEB_sites['same_sites']
        if len(self.BEB_sites['same_sites']) <= 0: #@ this condition prevents an error if the pickle file exists already
            for i in self.BEB_sites[keywithmaxval(self.BEB_sites)]:
                copy = True
                for aln in ('clus', 'mus', 'coff'):
                    if i not in self.BEB_sites[aln]:
                        copy = False
                if copy:
                    self.BEB_sites['same_sites'].append(i)
            if debug:
                print(self.BEB_sites)

    def print_info(self):

        # print(self.alignment['clus'][clade])
        # print(len(self.alignment['clus'][clade]))
        # print(len(trans(self.alignment['clus'][clade])))

        pamlerror = False
        ## make sure that these variable exists, return NA's if they don't
        if self.llvals['max_p']:

            try:
                M7_M8 = self.llvals[self.llvals['max_p'] + '_M7_M8_p']
            except:
                M7_M8 = 'NA'

            try:
                M8a = self.llvals[self.llvals['max_p'] + '_M8_M8a_p']
            except:
                M8a = 'NA'


            try:
                pa = len(trans(self.alignment['clus'][clade]))/len(self.ref_aa) * 100 #length of the ref_aa of the max pvalue divided by the reference
            except:
                pa = 'NA'

            if self.llvals['clus_M7_M8_p'] == 37767:
                pamlerror = True

        else:
            M7_M8 = 'NA'
            M8a = 'NA'

            try:
                pa = len(trans(self.alignment['clus'][clade]))/len(self.ref_aa) * 100
            except:
                pa = 'NA'

        ## make a variable of the species that were used for analysis
        self.species_used = []
        for key in self.alignment[self.llvals['max_p']]:
            self.species_used.append(key)

        numspec = len(self.species_used)

        ## make sure that these variable exists, return NA's if they don't
        if len(self.BEB_sites['same_sites']) == 0 or self.BEB_sites['same_sites'] == 'NA':
            self.BEB_sites['same_sites_number'] = 0
            self.BEB_sites['same_sites'] = 'NA'
            self.BEB_sites['average_sites'] = 'NA'
        else:
            self.BEB_sites['same_sites_number'] = len(self.BEB_sites['same_sites'])
            self.BEB_sites['average_sites'] = int((len(self.BEB_sites['clus'])
                                                  +len(self.BEB_sites['mus'])
                                                  +len(self.BEB_sites['coff']))/3)


        ## print command for all the output variables
        print('\n' + self.name
              + '\t' + str(M7_M8)
              + '\t' + str(M8a)
              + '\t' + str(self.BEB_sites['same_sites_number'])
              + '\t' + str(self.BEB_sites['same_sites']) + '\n')

        if pamlerror:
            pass
        else:
            with open(self.name + '/results.txt', 'a') as f: #@
                f.write('\n' + self.name
                        + '\t' + str(numspec)
                        + '\t' + str(len(self.ref_aa))
                        + '\t' + str(pa)
                        + '\t' + str(M7_M8)
                        + '\t' + str(M8a)
                        + '\t' + str(self.BEB_sites['average_sites'])
                        + '\t' + str(self.BEB_sites['same_sites_number'])
                        + '\t' + str(self.BEB_sites['same_sites'])
                        + '\t' + str(self.llvals['max_p']))


        with open(self.results_file(), 'w') as f:
            algnr = self.llvals['max_p']

            ##write results to file
            f.write('Gene name:\t' + self.name + '\n')
            f.write('Aligner with the least significant p-value:\t' + algnr + '\n')
            f.write('Number of species analyzed:\t' + str(len(self.species_used)) + '\t(' + ', '.join(self.species_used) + ')\n')
            f.write('M7-M8 pval:\t' + str(M7_M8) + '\n')
            f.write('M8-M8a pval:\t' + str(M8a) + '\n')
            f.write('Number of sites common with all aligners:\t' + str(self.BEB_sites['same_sites_number']) + '\n')
            f.write('Site positions:\t' + str(self.BEB_sites['same_sites']).strip('[]') + '\n\n')


            ## show the two sequences on top of each other
            site_write = True
            try:
                f.write('Clustal aligned sequence:  \t' + self.ref_min_aa['clus'] + '\n')
            except: ## for this one, if it was never made, make it here. This next bit is slightly modified from the site_get function above
                site_write = False

                ## extracts the D.mel reduced sequence form the PAML input file
                flag1 = False
                count = 0
                red_seq = []
                with open(self.paml_file('clus'),'r') as k:
                    for line in k.readlines():
                        if clade in line:
                            flag1 = True
                        if flag1 and count < 2:
                            line = [x.strip() for x in line]
                            line = ''.join(line)
                            red_seq.append(line)
                            count += 1

                ## two new properties that contain the reduced reference sequences
                self.ref_min_nt = {'clus' : red_seq[1]}
                self.ref_min_aa['clus'] = trans(self.ref_min_nt['clus'])

                ## iterate through the length of the main sequence. Check if the two are
                ## equal. If not, add a '-' to the reduced sequence, and check the next
                ## position. The result is that self.ref_min_aa has dashes and BEB sites
                ## in UPPER CASE, and is the same length as teh ref_aa sequence.
                for i in range(0,len(self.ref_aa)):
                    try:
                        if debug:
                            print(str(i) + ' - ' + self.ref_min_aa[i] + ' , ' + self.ref_aa[i])
                        if self.ref_min_aa[algnr][i].lower() != self.ref_aa[i].lower():
                            if i == 0:
                                self.ref_min_aa['clus'] = '-' + self.ref_min_aa['clus']
                            else:
                                self.ref_min_aa['clus'] = self.ref_min_aa['clus'][:i] + '-' + self.ref_min_aa['clus'][i:]
                    except:
                        pass
                self.ref_min_aa['clus'] = self.ref_min_aa['clus'].lower()

                ## finally, write it to the output file
                f.write('Clustal aligned sequence:  \t' + self.ref_min_aa['clus'] + '\n')

            try: ## try for Muscle
                f.write('Muscle aligned sequence:   \t' + self.ref_min_aa['mus'] + '\n')
            except: ## for these two, don't try and make them, just set to false
                site_write = False

            try: ## try for T-Coffee
                f.write('T-Coffee aligned sequence: \t' + self.ref_min_aa['coff'] + '\n')
            except:
                site_write = False

            f.write('Reference sequence:        \t' + self.ref_aa.lower() + '\n')

            ## generate the alignment for sites with a few aa on either side
            if site_write and self.BEB_sites['same_sites_number'] > 0 :
                f.write('\nAlignment of sites under selection:\n- Alignments are centered around the site, with 4 amino acids on either side. \n- There may be more than one site per alignment if they are close together. \n\n')
                for site in self.BEB_sites['same_sites']:
                    lower_bound = int(site - 5)
                    upper_bound = int(site + 4)
                    f.write('Site position:\t' + str(site) + '\n')
                    ref_min_aa_algnr = 'ref_min_aa_' + algnr
                    f.write('PAML sequence:\t' + self.ref_min_aa[algnr][lower_bound : upper_bound] + '\n')
                    f.write('Reference seq:\t' + self.ref_aa.lower()[lower_bound : upper_bound] + '\n\n')