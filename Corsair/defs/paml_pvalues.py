#!/usr/bin/env python3

import Corsair as cor

def paml_pvalues(iso):
    """Input: isoform object, Return: isoform object"""

    ## compute p-values, if the approprate values are present
    if iso.paml_results['logLvals']['M7'] and iso.paml_results['logLvals']['M8']:
        iso.paml_results['2delta']['M7M8'], iso.paml_results['pval']['M7M8'] = cor.log_ratio_test(iso.paml_results['logLvals']['M7'], iso.paml_results['logLvals']['M8'], 2)
    if iso.paml_results['logLvals']['M8'] and iso.paml_results['logLvals']['M8a']:
        iso.paml_results['2delta']['M8M8a'], iso.paml_results['pval']['M8M8a'] = cor.log_ratio_test(iso.paml_results['logLvals']['M8'], iso.paml_results['logLvals']['M8a'], 1)
    
    return iso