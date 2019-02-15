#!/bin/bash
set -eu

clade="bat_vamp"

local_path=$1
base=$(basename $local_path)
s3_path=s3://phadnislab-corsair/"$clade"_blast/$base
aws s3 cp $local_path $s3_path
instance_cpus=16
per_python_cpus=4
# jobs killed after 2 hours.
timeout=2h

chunk=1420

dir_name=`echo $base | cut -d. -f1`
mkdir $dir_name

## copy the python script to s3
aws s3 cp aws_corsair_blast_"$clade".py s3://phadnislab-corsair/python/

## how many times to loop based on chunck size and list length - note: this will
## always round up! So it is better to submit 399 items than 400, because 399
## will make 4 submissions whereas 400 would make 4 filled and 1 empty submission
line_num=`wc -l < $base`
run_cnt=$((($line_num/$chunk)+1))
## just a counting variable
measure=1

## for each chunck, make a temp list and submit that to aws
for i in $(seq 1 $run_cnt);do

  tempfile="$i.txt"
  s3_path=s3://phadnislab-corsair/tmp/$tempfile

  ## read the genes to a temp file and pipe that temp file to aws
  tail -n +$measure $base | head -$chunk > $tempfile
  measure=$(($measure+$chunk))

  ## batchit submitt commands. Check queue name and memory!
  aws s3 cp $tempfile $s3_path; echo $base $tempfile

  
  ./batchit_osx submit --queue c4-4xl \
        --role container-role --image blast \
        --region 'us-east-2' \
        --mem 28000 \
        --ebs "/mnt/local:120" \
        --cpus $instance_cpus \
        --envvars "iso_list=$s3_path" "cpus=$instance_cpus" "per_python_cpus=$per_python_cpus" "timeout=$timeout" \
        --jobname $(basename $s3_path .txt) \
        --jobname c4-4xl-blast-$dir_name-$i \
        "$clade"_BLAST.bpx.sh

  ## stagger sumbission by 90 seconds
  sleep 45

  # remove the temp file
  mv $tempfile $dir_name

done

<<OFF
cpus=64
batchit submit --queue m4-16x \
        --role container-role --image blast \
        --region 'us-east-2' \
        --mem 250000 \
        --volumes "/dev=/dev" \
        --cpus $instance_cpus \
        --envvars "iso_list=$s3_path" "cpus=$instance_cpus" "per_python_cpus=$per_python_cpus" "timeout=$timeout" \
        --jobname 500-test \
        BLAST.bpx.sh
OFF
