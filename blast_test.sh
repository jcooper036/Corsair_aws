#!/bin/bash
set -exuo pipefail

export AWS_DEFAULT_REGION=$region

## install batchit
curl -Lo /usr/bin/batchit http://home.chpc.utah.edu/~u6000771/batchit
chmod +x /usr/bin/batchit
pip install -U awscli

## install gargs
set +e
gargs --help || {
curl -Lo /usr/bin/gargs https://github.com/brentp/gargs/releases/download/v0.3.8/gargs_linux
chmod +x /usr/bin/gargs
}
set -e

df -h

# genes is a file containing a list of isos.
echo $cpus $gene_list $timeout

## get the command script if it is not there yet
if [[ ! -e $corsair_command ]]; then
  aws s3 cp ${s3_path}${corsair_command} $corsair_command
fi

## copy the Corsair module
mkdir Corsair
aws s3 cp --recursive s3://phadnisaws/Corsair/ Corsair/
ls -lh Corsair

## copy the project path
mkdir $project_path
aws s3 cp --exclude "genes" --recursive s3://phadnisaws/projects/$project_path/ $project_path/
ls -lh $project_path

## make the genomes directory, copy over the genomes. We don't actually need the fasta files, only the blast DB
mkdir /mnt/local/genomes
aws s3 cp --recursive $genomes_path /mnt/local/genomes/
ls -lh /mnt/local/genomes

export tblastn_threads=4
export clade

runner() {
    set -euo pipefail
    gene=$1

    /usr/bin/timeout $timeout python3 $corsair_command $gene $ctl_file
    (>&2 echo "$gene SUCESS!")
    aws s3 cp $project_path/genes/$gene/$gene.pkl s3://phadnisaws/projects/$project_path/genes/$gene/
    
    rm -f $project_path/genes/$gene/$gene.pkl
   (>&2 echo "COMPLETED $gene")
}
export -f runner

# check what's already there and dont re-run
aws s3 cp $gene_list .
gene_list=$(basename $gene_list)
wc -l $gene_list

# cpus is total cpus. and each process will use per_python cpus
# so we divide. NOTE that this requires they are multiples...
gargs_cpus=$((cpus / per_python_cpus))
gargs_cpus=$((gargs_cpus / tblastn_threads))

## do this in parallel with gargs
cat $gene_list | gargs -p $cpus -v "runner {}"