#!/usr/bin/env python3

def m7_m8_control_file(ctl, iso):
    """
    Input: control object, iso object
    Output: Writes a PAML control file to that file
    """
    output_file = iso.iso_files(ctl) + iso.name + '_PAML_M7M8_output.txt'
    iso.paml_output_files['M7M8'] = output_file
    
    ## Write/rewrite control file
    with open(iso.paml_control_file(ctl), 'w') as f:
        f.write('seqfile = ' + iso.iso_files(ctl) + iso.name +'.paml \n')
        f.write('treefile = ' + iso.iso_files(ctl) + iso.name + '_tree.txt \n')
        f.write('outfile = ' + output_file + ' \n')
        f.write('noisy = 3 \n')
        f.write('verbose = 1 \n')
        f.write('runmode = 0 \n')
        f.write('seqtype = 1 \n')
        f.write('CodonFreq = 2 \n')
        f.write('ndata = 1 \n')
        f.write('clock = 0  \n')
        f.write('aaDist = 0 \n')
        f.write('model = 0 \n')
        f.write('NSsites = 7 8 \n')
        f.write('icode = 0 \n')
        f.write('Mgene = 0 \n')
        f.write('fix_kappa = 0 \n')
        f.write('kappa = 2 \n')
        f.write('fix_omega = 0 \n')
        f.write('omega = 0.4 \n')
        f.write('fix_alpha = 1 \n')
        f.write('alpha = 0 \n')
        f.write('Malpha = 0 \n')
        f.write('ncatG = 8 \n')
        f.write('getSE = 0 \n')
        f.write('RateAncestor = 1 \n')
        f.write('Small_Diff = .5e-6 \n')
        f.write('cleandata = 1 \n')
        f.write('method = 0 \n')

def m8_m8a_control_file(ctl, iso):
    """
    Input: File name, isoform name
    Output: Writes a PAML control file to that file
    """
    output_file = iso.iso_files(ctl) + iso.name + '_PAML_M8a_output.txt'
    iso.paml_output_files['M8M8a'] = output_file

    #Write/rewrite control file
    with open(iso.paml_control_file(ctl), 'w') as f:
        f.write('seqfile = ' + iso.iso_files(ctl) + iso.name +'.paml \n')
        f.write('treefile = ' + iso.iso_files(ctl) + iso.name + '_tree.txt \n')
        f.write('outfile = ' + output_file + ' \n')
        f.write('noisy = 3 \n')
        f.write('verbose = 1 \n')
        f.write('runmode = 0 \n')
        f.write('seqtype = 1 \n')
        f.write('CodonFreq = 2 \n')
        f.write('ndata = 1 \n')
        f.write('clock = 0  \n')
        f.write('aaDist = 0 \n')
        f.write('model = 0 \n')
        f.write('NSsites = 8 \n')
        f.write('icode = 0 \n')
        f.write('Mgene = 0 \n')
        f.write('fix_kappa = 0 \n')
        f.write('kappa = 2 \n')
        f.write('fix_omega = 1 \n')
        f.write('omega = 1 \n')
        f.write('fix_alpha = 1 \n')
        f.write('alpha = 0 \n')
        f.write('Malpha = 0 \n')
        f.write('ncatG = 8 \n')
        f.write('getSE = 0 \n')
        f.write('RateAncestor = 1 \n')
        f.write('Small_Diff = .5e-6 \n')
        f.write('cleandata = 1 \n')
        f.write('method = 0 \n')
