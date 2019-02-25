FROM ubuntu:16.04
MAINTAINER Phadnis Lab <phadnis_aws@gmail.com>

RUN \
	apt-get clean && \
	apt-get update && \
	apt-get install -y python3 python3-pip emboss exonerate clustalo muscle t-coffee paml ncbi-blast+ nfs-common curl


RUN \
	pip3 install --upgrade pip==9.0.3 && \
	pip3 install docopt biopython scipy awscli pyfaidx && \
	curl -Lo /usr/bin/gargs https://github.com/brentp/gargs/releases/download/v0.3.8/gargs_linux && \
	chmod +x /usr/bin/gargs && \
	curl -Lo /usr/bin/batchit https://github.com/base2genomics/batchit/releases/download/v0.4.2/batchit && \
	chmod +x /usr/bin/batchit