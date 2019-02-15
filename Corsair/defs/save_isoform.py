#!/usr/bin/env python3

import pickle
import os

def save_isoform(ctl, iso):
    """
    Input: control object and an iso object
    Output: iso.pkl file for the isoform in projectdir/genes/iso/
    """

    iso_dir = ctl.project_path + 'genes/' + iso.name + '/'
    if os.path.isdir(iso_dir):
        with open(iso_dir + iso.name + '.pkl', 'wb') as output:
            pickle.dump (iso, output, pickle.HIGHEST_PROTOCOL)