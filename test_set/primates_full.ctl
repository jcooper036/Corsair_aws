### Primate project practice ###

## module directory. this is where the corsair directory is, absolute path
corsair_directory:/Users/Jacob/corsair/

## this is where all the files get stored. This does NOT have to be where the reference files are located, but any created files will go here
project_directory:/Users/Jacob/corsair/primates/

## reference CDS file, must be a cleaned fasta file. See README for more info.
reference_CDS:/Users/Jacob/corsair/primates/Human_reference_CDS.fasta

## this where all the genomes are located
genome_directory:/Volumes/Jacob_2TB_storage/primate_genomes/

## list of all the genes to run. They need to be a 1:1 exact match to the names in the ref CDS file.
gene_list:/Users/Jacob/corsair/primates/gene_list.txt

## clade tree (newick format). Names don't have to be 4 letters, but they MUST match the prefixes on genome files. No spaces.
tree:(((((((Ptro,Ppan),Hsap),Ggor),Pabe),Nleu),(((((Mfas,Mmul),Mnem),(Panu,(Caty,Mleu))),Csab),(Cang,(Nlar,Rbie)))),((Sbol,Ccap),Cjac));

## reference species - in the tree listed above, this is the reference
ref_spec:Hsap

## minimum species count - this is the fewest species that PAML will be attempted with. min:3, max:species_count, default:0.7*species_count
minimum_species:3

## alignment threshold - this is the alignment threshold for identifying genes. min:0.7, max:1, default:0.95
alignment_threshold:0.80

## alingers - name of the aligners, in order, comma seperated, no spaces. Default is clustal, tcoffee, muscle, M8 . Lots more to be done to change these, generally leave the same
aligners:clustal,tcoffee,muscle,M8

## BEB threshold - what does the posterior probability of the BEB analysis need to be to be considered a hit? Default: 0.95
BEB_threshold:0.95

## blast scaffolds - if there are pre-computed blast scaffolds, where are they?
blast_scaffolds: