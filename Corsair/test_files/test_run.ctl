### Primate project practice ###

## module directory. this is where the corsair directory is, absolute path
corsair_directory:/Users/Jacob/corsair/

## this is where all the files get stored. This does NOT have to be where the reference files are located, but any created files will go here
project_directory:/Users/Jacob/corsair/Corsair/test_files/

## reference CDS file, must be a cleaned fasta file. See README for more info.
reference_CDS:/Users/Jacob/corsair/Corsair/test_files/Hsap_reference_CDS.fasta

## this where all the genomes are located
genome_directory:/Users/Jacob/corsair/Corsair/test_files/testing_genomes/

## list of all the genes to run. They need to be a 1:1 exact match to the names in the ref CDS file.
gene_list:/Users/Jacob/corsair/Corsair/test_files/test_gene_list.txt

## clade tree (newick format). Names don't have to be 4 letters, but they MUST match the prefixes on genome files. No spaces.
tree:(((((Ptro,Ppan),Hsap),Ggor),Nleu),((Mfas,Mmul),Cang));

## reference species - in the tree listed above, this is the reference
ref_spec:Hsap

## minimum species count - this is the fewest species that PAML will be attempted with. min:3, max:species_count, default:0.7*species_count
minimum_species:3

## alignment threshold - this is the alignment threshold for identifying genes. min:0.7, max:1, default:0.95
alignment_threshold:0.95

## alingers - name of the aligners, in order, comma seperated, no spaces. Default is clustal, tcoffee, muscle, M8 . Lots more to be done to change these, generally leave the same
aligners:clustal,tcoffee,muscle,M8    