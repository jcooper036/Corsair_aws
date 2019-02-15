#!/usr/bin/env python3

def sample_ctl(file):
    """
    Generates a sample control file in the current working directory
    """
    with open (file, 'w+') as f:
        f.write(
            "### CTL Example file ###\n\n" +
            "## For all file paths, it is best to specify the absolute path. This is because things may be scattered in many directories\n\n"
            "## module directory. this is where the corsair directory is, absolute path\n"
            "corsair_directory:/Users/$USR_NAME/corsair/\n\n"
            "## this is where all the files get stored. This does NOT have to be where the reference files are located, but any created files will go here\n" +
            "project_directory:/Users/$USR_NAME/corsair/primates/\n\n" +
            "## reference CDS file, must be a cleaned fasta file. See README for more info.\n" +
            "reference_CDS:/Users/$USR_NAME/corsair/primates/reference_CDS.fasta\n\n" +            
            "## this where all the genomes are located\n" +
            "genome_directory:/Users/$USR_NAME/corsair/primates/genomes/\n\n" +
            "## list of all the genes to run. They need to be a 1:1 exact match to the names in the ref CDS file.\n" +
            "gene_list:/Users/$USR_NAME/corsair/primates/gene_list.txt\n\n" +            
            "## clade tree (newick format). Names don't have to be 4 letters, but they MUST match the prefixes on genome files\n" +
            "tree:(((((Ptro,Ppan),Hsap),Ggor),((Mfas,Mmul),(Caty,Mleu))),Sbol);\n\n" +  
            "## reference species - in the tree listed above, this is the reference\n" +
            "ref_spec:Hsap\n\n" +
            "## minimum species count - this is the fewest species that PAML will be attempted with. min:3, max:species_count, default:0.7*species_count\n" +
            "minimum_species:3\n\n" +
            "## alignment threshold - this is the alignment threshold for identifying genes. min:0.7, max:1, default:0.95\n" +
            "alignment_threshold:0.95\n\n" +
            "## alingers - name of the aligners, in order, comma seperated, no spaces. Default is clustal, tcoffee, muscle, M8 . Lots more to be done to change these, generally leave the same\n" +
            "aligners:clustal,tcoffee,muscle,M8\n\n" +
            "## BEB threshold - what does the posterior probability of the BEB analysis need to be to be considered a hit? Default: 0.95\n" +
            "BEB_threshold:0.95\n\n" +
            "## blast scaffolds - if there are pre-computed blast scaffolds, where are they?\n" +
            "blast_scaffolds:/Users/$USR_NAME/corsair/primates/scaffolds/\n\n"           
        )
