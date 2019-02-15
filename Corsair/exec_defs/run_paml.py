#!/usr/bin/env python3

import Corsair as cor
import os

def run_paml_M7M8(ctl, iso_name):
    """
    Input: control object, isoform name, alinger name
    Output: PAML results file, updated isoform object
    """
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    paml_input = iso.iso_files(ctl) + iso.name +'.paml'
    tree_file = iso.iso_files(ctl) + iso.name + '_tree.txt'

    ## check to make sure that the files that are needed are there
    if (not os.path.isfile(paml_input)) or (not os.path.isfile(tree_file)):
        print('WARNING: No PAML input and/or tree file for {}, aborting PAML'.format(iso.name))
        return None

    print('Running PAML(M7 vs M8) for {}'.format(iso.name))

    ## write the control file
    cor.m7_m8_control_file(ctl, iso)

    ## run codeml
    command = ctl.mod_path + 'Corsair/bin/paml/4.9e/bin/codeml ' + iso.paml_control_file(ctl)
    cor.shell(command)

    ## remove all the files codeml leaves behind
    try:
        for f in ['2NG.dN','2NG.dS','2NG.t','4fold.nuc','lnf','rst','rst1','rub']:
            os.remove(os.getcwd() + '/' + f)
    except:
        pass
    
    print("PAML complete for {}".format(iso.name))  

    ## save the isoform object
    cor.save_isoform(ctl, iso)

def run_paml_M8M8a(ctl, iso_name):
    """
    Input: control object, isoform name, alinger name
    Output: PAML results file, updated isoform object
    """
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## check the previous p-value, and that it was run:
    if iso.paml_results['pval']['M7M8']:
        if not iso.paml_results['pval']['M7M8'] < 0.05:
            return None
    else:
        return None

    print('Running PAML(M8 vs M8a) for {}'.format(iso.name))

    ## write the control file
    cor.m8_m8a_control_file(ctl, iso)

    ## run codeml
    command = ctl.mod_path + 'Corsair/bin/paml/4.9e/bin/codeml ' + iso.paml_control_file(ctl)
    cor.shell(command)

    ## remove all the files codeml leaves behind
    try:
        for f in ['2NG.dN','2NG.dS','2NG.t','4fold.nuc','lnf','rst','rst1','rub']:
            os.remove(os.getcwd() + '/' + f)
    except:
        pass
    
    print("PAML complete for {}".format(iso.name))  

    ## save the isoform object
    cor.save_isoform(ctl, iso)