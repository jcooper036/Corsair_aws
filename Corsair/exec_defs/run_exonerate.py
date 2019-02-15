#!/usr/bin/env python3

import Corsair as cor
import os

def run_exonerate(ctl, iso_name):
    """
    Input: control object, isoform name
    Output: modifies the isoform save file to include the exonerate result
    """
    ## load the isoform object
    iso = cor.load_isoform(ctl, iso_name)

    ## check for what exonerate needs
    missing = []
    for species in ctl.genome_paths:
        if not ctl.genome_paths[species]:
            missing.append(species)
    if missing:
        print("ERROR: Could not find genomes for {}, aborting exonerate".format(missing))
        return None

    print('Running exonerate for ' + iso.name)

    ## check that the temp directory exists
    temp_dir = ctl.project_path + 'temp/'
    if not os.path.isdir(temp_dir):
        os.mkdir(temp_dir)
    if not os.path.isdir(iso.iso_files(ctl)):
        os.mkdir(iso.iso_files(ctl))  

    ## write the protein sequence
    temp = {ctl.ref_species : iso.ref_aa}
    cor.write_fasta(iso.protein_file(ctl), temp, [ctl.ref_species])

    ############ run exonerate
    # iterate over the list of scaffolds from each species
    for species, scaffold in iso.scaffolds.items():
        if species != ctl.ref_species:
            print(species + ' scaffold for ' + iso.name + ': ' + scaffold)
            
            ## write the scaffold to a temporary file
            genome_path = ctl.genome_paths[species]
            cor.shell('samtools faidx ' + genome_path + ' ' + scaffold + ' > ' + temp_dir + species + '_' + iso.name + '.fasta')

            #exonerates through scaffold using input protein
            input_scaffold_file = temp_dir + species + '_' + iso.name + '.fasta'
            results_file = iso.iso_files(ctl) + species
            command = ctl.mod_path + 'Corsair/bin/exonerate/2.2.0/bin/exonerate --model protein2genome --query ' + iso.protein_file(ctl) + ' --target ' + input_scaffold_file + ' --ryo "forcebeams \n>' + species + '\n%tcs\n" --bestn 1 > ' + results_file + '.txt'
            cor.shell(command)

            #removes temporary scaffold (mitigating measure for parallel)
            os.remove(input_scaffold_file)

    ## save the isoform object
    cor.save_isoform(ctl, iso)
