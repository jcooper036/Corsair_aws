#!/bin/bash
set -exuo pipefail

## set all of these before running
python_script="aws_corsair_bat_vamp_id_ml.py"
s3_blast_data="bat_blast-data"
results_folder="results_180328_bat_vamp_unique"
isoform_sequence_file="Pteropus_vampyrus_all_isoform_fasta_cds.pkl"
blast_scaffold_file="180328_bat_vamp_blast_scaffolds.pkl"

#################################3
#################################3
cd $TMPDIR
df -h

## change this for running 9 species vs all species
# aws s3 cp s3://phadnislab-corsair/python/aws4b_corsair_id_ml_down_sample.py .
aws s3 cp s3://phadnislab-corsair/python/"$python_script" .

aws s3 cp s3://phadnislab-corsair/"$s3_blast_data"/"$isoform_sequence_file" ./blast-data/
aws s3 cp s3://phadnislab-corsair/"$s3_blast_data"/"$blast_scaffold_file" ./blast-data/

set +e
aws s3 sync --exclude "*" --include "*.fasta" --include "*.fai" s3://phadnislab-corsair/"$s3_blast_data"/ ./blast-data/
aws s3 sync --exclude "*" --include "*.fasta" --include "*.fai" s3://phadnislab-corsair/"$s3_blast_data"/ ./blast-data/
set -e

export gdir=$(pwd)/"$s3_blast_data"/
export python_script
export results_folder

mkdir -p temp

per_gene() {
    set -exuo pipefail
    gene=$1
    mkdir -p "$gene"/"$gene"_files
    ## set as an environmental variable
    echo $gene

    ## Run IDML - change this line for changing run script
    /usr/bin/timeout $timeout python3 "$python_script" "$gene"

    ##Export results files to e3 location (if the directory exists)
    if [ -d "$gene" ]
    then
      ##moves results to e3
      printf 'Transferring results to S3.'
      # TODO: don't hard-code results171026
      ## save file location
      aws s3 sync "$gene"/ s3://phadnislab-corsair/"$results_folder"/"$gene"/
      rm -rf "$gene"
    fi
}
export -f per_gene

aws s3 cp $iso_list .
iso_list=$(basename $iso_list)
# TODO: copy BLAST.bp.sh to avoid re-doing work by doing aws s3 ls on output

cat $iso_list \
    | gargs -p $cpus -v "per_gene {}"
