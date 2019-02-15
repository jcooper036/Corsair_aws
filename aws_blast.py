#!/usr/bin/env python3
"""
Usage: by_gene.py <isoform> <ctl_file>

Arguments:
    <isoform>     Name of the isoform to be run
    <ctl_file>    Path to ctl file

"""
#imports
import docopt
import Corsair as cor
import sys

## Initialize docopt
if __name__ == '__main__':

    try:
        arguments = docopt.docopt(__doc__)
        iso_name = str(arguments['<isoform>'])
        ctl_file = str(arguments['<ctl_file>'])
    except docopt.DocoptExit as e:
        print(e)

## parse the ctl file, initialize the control object
ctl = cor.load_ctl(ctl_file)

## a few things rely of the gene list being here, so just make it a one item list
ctl.gene_list = [iso_name]

## for the first time only - will over-write saves otherwise
cor.corsair_initialize(ctl)

# # just do blast and exonerate
cor.run_blast(ctl, iso_name)
# cor.run_exonerate(ctl, iso_name)
# cor.load_species_sequences(ctl, iso_name)

# # # just do the alignment and PAML (if Blast and Exonerate are already done)
# cor.align_and_paml(ctl, iso_name)

# # ## run all the results gathering functions for the whole gene list
# cor.read_paml_output(ctl, iso_name)

# ## read get results
# cor.results_processing(ctl, iso_name)
