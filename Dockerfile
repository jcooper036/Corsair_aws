FROM ubuntu:16.04
MAINTAINER Phadnis Lab <phadnislab1@gmail.com>



RUN \
	apt-get clean &&\
	apt-get update &&\
	apt-get install -y python3 python3-pip ncbi-blast+ nfs-common curl &&\
	pip3 install --upgrade pip &&\
	pip3 install docopt biopython scipy awscli pyfaidx &&\
	curl -Lo /usr/bin/gargs https://github.com/brentp/gargs/releases/download/v0.3.8/gargs_linux &&\
	chmod +x /usr/bin/gargs &&\
	curl -Lo /usr/bin/batchit http://home.chpc.utah.edu/~u6000771/batchit &&\
	chmod +x /usr/bin/batchit
