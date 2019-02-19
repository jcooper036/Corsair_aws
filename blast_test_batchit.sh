#!/bin/bash
set -eu

#############################################
#############################################
############### CHECK THESE VARIABLES

############# aws settings
#######################################

## aws user name
username=phadnisaws

## instace CPUs
instance_cpus=16

## jobs killed after 2 hours.
timeout=2h

## queue name
queue_name=blast_queue_02

## image
image=corsair_container:latest

## role name
role=worker-role

## memory
memory=28000

## server region
region=us-east-2

## CPUs per python
per_python_cpus=4

####### corsair settings
#######################################
## the gene list
gene_list=/Users/Jacob/Corsair_aws/test_set/testing_gene_list_2.txt

## the control file - this gets used once on EC2
ctl_file=test_set/primates_test.ctl

## project file
project_path=test_set

## s3 path
s3_path=s3://${username}/projects/$project_path/

## genomes
genomes_path=s3://${username}/genomes/primates/

## corsair command
corsair_command=aws_blast.py

## chunk size
chunk=1420

############### END OF VARIABLES
#############################################
#############################################


## copy the gene list
aws s3 cp $gene_list $s3_path

## make a file with the gene list name
dir_name=`echo $gene_list | cut -d. -f1`
[[ -d $dir_name ]] || mkdir $dir_name

## copy the module and the specific script to execute
aws s3 cp $corsair_command $s3_path

## copy the project to s3 #@
aws s3 sync $project_path s3://${username}/projects/$project_path

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
  partial_gene_list=s3://${username}/tmp/$tempfile

  ## read the genes to a temp file and pipe that temp file to aws
  tail -n +$measure $gene_list | head -$chunk > $tempfile
  measure=$(($measure+$chunk))

  ## batchit submitt commands. Check queue name and memory!
  aws s3 cp $tempfile $partial_gene_list

  
  ./batchit_osx submit --queue ${queue_name} \
        --role ${role} --image ${image} \
        --region ${region} \
        --mem ${memory} \
        --ebs "/mnt/local:120" \
        --cpus $instance_cpus \
        --envvars "timeout=$timeout" "region=$region" "gene_list=$partial_gene_list" "cpus=$instance_cpus" "per_python_cpus=$per_python_cpus" "genomes_path=$genomes_path" "corsair_command=$corsair_command" "s3_path=$s3_path" "project_path=$project_path" "ctl_file=$ctl_file"\
        --jobname ${project_path}_${i} \
        blast_test.sh

  ## stagger sumbission by 90 seconds
  sleep 5

  # remove the temp file
  mv $tempfile $dir_name

done
