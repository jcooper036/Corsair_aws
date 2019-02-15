#!/usr/bin/env python3

import Corsair as cor

def dnds_processing(ctl, iso_name):
    """
    Input: control object, iso name
    Output: maxes and averages for dNdS, saves isoform object
    """    
    
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## don't do anything if there are no results
    if not iso.dnds['list_ds']:
        return None 

    ## max ds
    iso.dnds['max_ds'] = max(iso.dnds['list_ds'])

    ## list out dNdS from the dNdS tuples
    for pair in iso.dnds['tuple_dnds']:
        if pair[1] > 0:
            iso.dnds['list_dnds'].append(pair[0]/pair[1])
    
    ## calculate the average dNdS
    iso.dnds['av_dnds'] = sum(iso.dnds['list_dnds']) / len(iso.dnds['list_dnds'])

    ## save the isoform object
    cor.save_isoform(ctl, iso)