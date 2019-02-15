#!/bin/bash

## job name
jn=idml-m4-4x
timeout=4h
## must change per instance!
instance_cpus=16
## how many genes will be submitted to each instance
chunk=228
python_script="aws_corsair_bat_vamp_id_ml.py"

## path variables
local_path=$1
base=$(basename $local_path)


## how many times to loop based on chunck size and list length - note: this will
## always round up! So it is better to submit 399 items than 400, because 399
## will make 4 submissions whereas 400 would make 4 filled and 1 empty submission
line_num=`wc -l < $base`
run_cnt=$((($line_num/$chunk)+1))
## just a counting variable
measure=1

## makes a directory with the base file name to put the lists in
dir_name=`echo $base | cut -d. -f1`
mkdir $dir_name

## delete and re-upload the python script to s3
aws s3 rm s3://phadnislab-corsair/python/"$python_script"
aws s3 cp "$python_script" s3://phadnislab-corsair/python/


## for each chunck, make a temp list and submit that to aws
for i in $(seq 1 $run_cnt);do

  tempfile="$i.txt"
  s3_path=s3://phadnislab-corsair/tmp/$tempfile

  ## read the genes to a temp file and pipe that temp file to aws
  tail -n +$measure $base | head -$chunk > $tempfile
  measure=$(($measure+$chunk))

  ## batchit submitt commands. Check queue name and memory!
  aws s3 cp $tempfile $s3_path; echo $base $tempfile

  ./batchit_osx submit \
    --queue m4-4x \
    --mem 58000 \
    --cpus $instance_cpus \
    --ebs "/mnt/local:120" \
    --role container-role --image corsair_id_ml \
    --region 'us-east-2' \
    --envvars "iso_list=$s3_path" "cpus=$instance_cpus" "timeout=$timeout" \
    --jobname $jn-idml-$dir_name-$i \
     idml.sh

  ## stagger sumbission by 30 seconds
  sleep 30

  # remove the temp file
  mv $tempfile $dir_name

done
