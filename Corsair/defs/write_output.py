#!/usr/bin/env python3

import Corsair as cor
from datetime import datetime

def write_output(ctl):
    """
    Input: control file
    Output: write results to date_results.txt in the project folder
    """    
    
    # header
    results = ['Gene'
        + '\t' + 'Ensembl_ID'
        + '\t' + 'Species'
        + '\t' + 'Reference_length(aa)'
        + '\t' + 'Percent_analyzed'
        + '\t' + 'Average_dNdS'
        + '\t' + 'Maximum_dS'
        + '\t' + 'Average_M7_tree'
        + '\t' + 'Average_M8_tree'
        + '\t' + 'M7_log_likelihood'
        + '\t' + 'M8_log_likelihood'
        + '\t' + 'M7-M8_p_value'
        + '\t' + 'M8a_log_likelihood'
        + '\t' + 'M8-M8a_pvalue'
        + '\t' + 'BEB_hits(pp>' + str(ctl.beb_threshold) + ')'
        + '\t' + 'BEB_sites'
    ]

    ## loop over each isoform
    for iso_name in ctl.gene_list:

        ## load the isoform object
        iso = cor.load_isoform(ctl, iso_name)

        ## hedge against the isoform not being there - will print an error though
        if not iso:
            continue

        ## function below
        results.append(result_line(iso, ctl))

        ## write each gene to it's output file
        cor.write_gene_results(iso, ctl)
        
        ## save the isoform object
        cor.save_isoform(ctl, iso)

    ## get the date, name  the file with it
    now = datetime.now().strftime("%Y-%m-%d-%H-%M")
    result_file = ctl.project_path + now + '_' +  ctl.ref_species + '_results.txt'

    ## open an write to the results file
    with open(result_file, 'w') as f:
        for line in results:
            f.write(str(line) + '\n')

def result_line(iso, ctl):
    """
    Input: Isoform object
    Returns: String that is meant to go into the results list
    """
    ## go through the variables, make sure they exist

    ## gene
    gene = iso.name + '\t'
    
    ## ensembl ID
    if iso.ensembl:
        ensembl = iso.ensembl + '\t'
    else:
        ensembl = '\t'
    
    ## species
    if iso.good_species:
        species = str(len(iso.good_species)) + '\t'
    else:
        species = '1\t'
    
    ## reference length
    ref_len = str(len(iso.ref_aa)) + '\t'

    ## percent analyzed
    if iso.trimmed:
        percent = str(len(iso.trimmed[ctl.ref_species])/ len(iso.ref_aa) * 100) + '\t'
    else:
        percent = '\t'
    
    ## average dNdS
    if iso.dnds['av_dnds']:
        av_dnds = str(iso.dnds['av_dnds']) + '\t'
    else:
        av_dnds = '\t'

    ## max dS
    if iso.dnds['max_ds']:
        max_ds = str(iso.dnds['max_ds']) + '\t'
    else:
        max_ds = '\t'

    ## average M7 tree
    if iso.tree_length['M7']:
        m7_tree = str(iso.tree_length['M7']) + '\t'
    else:
        m7_tree = '\t'

    ## average M8 tree
    if iso.tree_length['M8']:
        m8_tree = str(iso.tree_length['M8']) + '\t'
    else:
        m8_tree = '\t'
    
    ## M7_log_likelihood
    if iso.paml_results['logLvals']['M7']:
        llvalM7 = str(iso.paml_results['logLvals']['M7']) + '\t'
    else:
        llvalM7 = '\t'

    ## M8_log_likelihood
    if iso.paml_results['logLvals']['M8']:
        llvalM8 = str(iso.paml_results['logLvals']['M8']) + '\t'
    else:
        llvalM8 = '\t'

    ## M7-M8 pvalue
    if iso.paml_results['pval']['M7M8']:
        m7m8 = str(iso.paml_results['pval']['M7M8']) + '\t'
    else:
        m7m8 = '\t'

    ## M8_log_likelihood
    if iso.paml_results['logLvals']['M8a']:
        llvalM8a = str(iso.paml_results['logLvals']['M8a']) + '\t'
    else:
        llvalM8a = '\t'

    ## M8-M8a pvalue
    if iso.paml_results['pval']['M8M8a']:
        m8m8a = str(iso.paml_results['pval']['M8M8a']) + '\t'
    else:
        m8m8a = '\t'

    ## BEB hits
    if iso.paml_results['beb_hit_sites']:
        hits = str(len(iso.paml_results['beb_hit_sites'])) + '\t'
        sites = manage_bebs(iso.paml_results['beb_hit_sites']) + '\t'
    else:
        hits = '\t'
        sites = '\t'
    
    ## only do it this way for readability
    string = [
        gene
        + ensembl
        + species
        + ref_len
        + percent
        + av_dnds
        + max_ds
        + m7_tree
        + m8_tree
        + llvalM7
        + llvalM8
        + m7m8
        + llvalM8a
        + m8m8a
        + hits
        + sites
    ]

    return string[0]

def manage_bebs(beb_dict):
    """
    Input: The BEB site dictionary. Return: string of BEB sites
    """
    ret_string = []
    for entry in beb_dict:
        piece = str(beb_dict[entry]['ID']) + str(entry)
        ret_string.append(piece)
    ret_string = ", ".join(ret_string)
    return ret_string