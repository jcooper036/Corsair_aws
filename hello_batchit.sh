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

./batchit_osx submit --queue ${queue_name} \
    --role ${role} --image ${image} \
    --region ${region} \
    --mem ${memory} \
    --ebs "/mnt/local:120" \
    --cpus $instance_cpus \
    --envvars "timeout=$timeout" "region=$region" \
    --jobname hello_world \
    hello_world.sh