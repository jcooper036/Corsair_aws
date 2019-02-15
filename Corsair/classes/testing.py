#!/usr/bin/env python3

import os
import pickle
from scipy.stats import chi2

file='/Users/Jacob/corsair/primates/genes/EIF2AK2/EIF2AK2_files/EIF2AK2_PAML_M7M8_output.txt'

paml_results = {
    'logLvals' : {'M7' : False, 'M8' : False, 'M8a' : False},
    '2delta' : {'M7M8' : False, 'M8M8a' : False},
    'pval' : {'M7M8' : False, 'M8M8a' : False},
    'beb_sites_raw' : {}
}

def read_paml_file(file, paml_results):
    """
    Input : PAML output file and isoform object
    - Only reads the raw data from the file, no processing
    Output : Returns isoform object
    """
    
    with open(file, 'r') as f:
        ready = False
        record_beb = False

        for line in f.readlines():
            line = line.strip()
            
            ## identify the model
            if "Model" in line:
                model = 'M8a' # this is default because it never shows up in M8a file
                if 'Model 7' in line:
                    model = 'M7'
                if 'Model 8' in line:
                    model = 'M8'
            
            ## find the log-liklihood values
            if "lnL" in line:
                line = line.replace(' ','').split(':')[3].split('+')[0]
                paml_results['logLvals'][model] = float(line)
            

            ## dNdS values


            ## Tree lengths


            ## BEB sites
            if record_beb:
                entry = line.split()
                if entry:
                    if entry[0].isdigit():
                        s_num = int(entry[0])
                        s_id = entry[1]
                        s_beb = float(entry[2])
                        paml_results['beb_sites_raw'][s_num] = {'ID' : s_id, 'BEB' : s_beb}

            if 'Bayes Empirical Bayes (BEB)' in line:
                ready = True
            if 'Pr(w>1)' in line and ready:
                record_beb = True
            if 'grid ' in line:
                record_beb = False

    
    return paml_results


print(read_paml_file(file, paml_results))