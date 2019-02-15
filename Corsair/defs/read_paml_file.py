#!/usr/bin/env python3

import Corsair as cor

def read_paml_file(file, iso):
    """
    Input : PAML output file and isoform object
    - Only reads the raw data from the file, no processing
    Output : Returns isoform object
    """
    
    with open(file, 'r') as f:
        ready = False
        record_beb = False
        dnds_cap = False

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
                iso.paml_results['logLvals'][model] = float(line)
            
            ## dNdS values
            if 'Model 7: beta (10 categories)' in line:
                dnds_cap = False
            
            if dnds_cap and not iso.dnds['recorded']:
                if len(line) > 0:
                    for ele in line.split():
                        if '(' in ele:
                            dnds = False
                            dn = float(ele.split('(')[1])
                        if ')' in ele:
                            ds = float(ele.split(')')[0])
                            dnds = (dn,ds)
                            iso.dnds['list_ds'].append(ds)
                            iso.dnds['list_dn'].append(dn)
                            iso.dnds['tuple_dnds'].append(dnds)

            if 'Use runmode = -2 for ML pairwise comparison.)' in line:
                dnds_cap = True

            ## Tree lengths
            if ('tree length =' in line) and (model != 'M8a'):
                iso.tree_length[model] = float(line.split()[3])

            ## BEB sites
            if record_beb:
                entry = line.split()
                if entry:
                    if entry[0].isdigit():
                        s_num = int(entry[0])
                        s_id = entry[1]
                        s_beb = float(entry[2].replace('*', ''))
                        iso.paml_results['beb_sites_raw'][s_num] = {'ID' : s_id, 'BEB' : s_beb}

            if 'Bayes Empirical Bayes (BEB)' in line:
                ready = True
            if 'Pr(w>1)' in line and ready:
                record_beb = True
            if 'grid ' in line:
                record_beb = False

    iso.dnds['recorded'] = True

    return iso