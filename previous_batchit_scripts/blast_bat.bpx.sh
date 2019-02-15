#!/bin/bash
set -exuo pipefail

# apt-get clean
# apt-get update
# apt-get install -y curl
export AWS_DEFAULT_REGION=us-east-2

clade="bat_vamp"
cladeshort="bat" ## made for this run so that I can querey the existing bat files

curl -Lo /usr/bin/batchit http://home.chpc.utah.edu/~u6000771/batchit
chmod +x /usr/bin/batchit
pip install -U awscli

# vid=$(batchit ebsmount --size 120 -m /mnt/local -n 1)
# trap "umount -l /mnt/local; batchit ddv $vid" EXIT
df -h

# cd /mnt/local
# export TMPDIR=/mnt/local

# genes is a file containing a list of isos.
echo $cpus $iso_list $timeout

if [[ ! -e aws_corsair_blast.py ]]; then
  aws s3 cp s3://phadnislab-corsair/python/aws_corsair_blast_"$clade".py aws_corsair_blast.py
fi


set +e
gargs --help || {
curl -Lo /usr/bin/gargs https://github.com/brentp/gargs/releases/download/v0.3.8/gargs_linux
chmod +x /usr/bin/gargs
}

set -e

mkdir "$clade"_blast-data
aws s3 cp --exclude "*.fasta" --recursive s3://phadnislab-corsair/"$cladeshort"_blast-data/ ./"$clade"_blast-data/
ls -lh "$clade"_blast-data/
ls -lh

export gdir=$(pwd)/"$clade"_blast-data/
ls -lh $gdir/*.pkl

export tblastn_threads=4
export clade

runner() {
    set -euo pipefail
    gene=$1

    /usr/bin/timeout $timeout python3 aws_corsair_blast.py $gene $gdir $per_python_cpus $tblastn_threads
    if [ -e "$gene"_scaffolds.txt ]
    then
      (>&2 echo "$gene Transferring scaffolds to S3.")
      aws s3 cp "$gene"_scaffolds.txt s3://phadnislab-corsair/blast_results_"$clade"/
    else
      (>&2 echo "$gene No scaffold file found.")
      touch "$gene"_error.txt
      aws s3 cp "$gene"_error.txt s3://phadnislab-corsair/blast_results_"$clade"/
    fi

    rm -f "$gene"_scaffolds.txt
   (>&2 echo "COMPLETED $gene")
}
export -f runner

# check what's already there and dont re-run
# aws s3 ls s3://phadnislab-corsair/blast_results_"$clade"/ | awk '{ print $NF }' | perl -pe 's/_scaffolds.txt//' > existing-genes.txt
aws s3 cp $iso_list .
iso_list=$(basename $iso_list)
wc -l $iso_list
# grep -cvwf existing-genes.txt $iso_list

# cpus is total cpus. and each process will use per_python cpus
# so we divide. NOTE that this requires they are multiples...
gargs_cpus=$((cpus / per_python_cpus))
gargs_cpus=$((gargs_cpus / tblastn_threads))

# grep -vwf existing-genes.txt $iso_list \
#    | gargs -p $gargs_cpus -v "runner {}"

cat $iso_list
# cat $iso_list | gargs -p $gargs_cpus -v "runner {}"
cat $iso_list | gargs -p $cpus -v "runner {}"