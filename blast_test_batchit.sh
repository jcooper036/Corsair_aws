#!/bin/bash
set -eu

####### corsair settings
## the control file - this gets used once on EC2
ctl_file=test_set/primates_test.ctl

## the gene list
gene_list=/Users/Jacob/Corsair_aws/test_set/testing_gene_list_1.txt

## project file
project_path=test_set

## genomes
genomes_path=s3://phadnisaws/genomes/primates/

## corsair command
corsair_command=aws_blast.py

## s3 path
s3_path=s3://phadnisaws/projects/testing

############# aws settings
## instace CPUs
instance_cpus=16

## CPUs per python
per_python_cpus=4

## jobs killed after 2 hours.
timeout=2h

## chunk size
chunk=1420





## copy the gene list
aws s3 cp $gene_list $s3_path

## make a file with the gene list name
dir_name=`echo $gene_list | cut -d. -f1`
[[ -d $dir_name ]] || mkdir $dir_name

## copy the module and the specific script to execute
aws s3 cp $corsair_command $s3_path

## copy the project to s3
aws s3 sync $project_path s3://phadnisaws/projects/

## how many times to loop based on chunck size and list length - note: this will
## always round up! So it is better to submit 399 items than 400, because 399
## will make 4 submissions whereas 400 would make 4 filled and 1 empty submission
line_num=`wc -l < $gene_list`
run_count=$((($line_num/$chunk)+1))
## just a counting variable
measure=1

## for each chunck, make a temp list and submit that to aws
for i in $(seq 1 $run_count);do

  tempfile="$i.txt"
  partial_gene_list=s3://phadnisaws/tmp/$tempfile

  ## read the genes to a temp file and pipe that temp file to aws
  tail -n +$measure $gene_list | head -$chunk > $tempfile
  measure=$(($measure+$chunk))

  ## batchit submitt commands. Check queue name and memory!
  aws s3 cp $tempfile $partial_gene_list; echo $gene_list $tempfile

  
  ./batchit_osx submit --queue corsair_env_001 \
        --role admin_roll --image corsair_env \
        --region 'us-east-1' \
        --mem 28000 \
        --ebs "/mnt/local:120" \
        --cpus $instance_cpus \
        --envvars "gene_list=$partial_gene_list" "cpus=$instance_cpus" "per_python_cpus=$per_python_cpus" "timeout=$timeout" "genomes_path=$genomes_path" "corsair_command=$corsair_command" "s3_path=$s3_path"\
        --jobname ${project_path}_${i} \
        blast_test.sh

  ## stagger sumbission by 90 seconds
  sleep 5

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
