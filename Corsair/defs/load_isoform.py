#!/usr/bin/env python3

import Corsair as cor
import os
import pickle

def load_isoform(ctl, iso_name):
    """
    input : control object (ctl), isoform name
    output : iso object
    """

    pkl_file = "{}/genes/{}/{}.pkl".format(ctl.project_path, iso_name, iso_name)
    if os.path.exists(pkl_file):
        with open(pkl_file, 'rb') as f:
            iso = pickle.load(f)
    else:
        print("ERROR: Could not load data for " + iso_name + " - This is usually caused by the gene list having a mis-spelling")
        return None
    
    return iso