#!/bin/bash
set -exuo pipefail

export AWS_DEFAULT_REGION=$region

## install batchit
curl -Lo /usr/bin/batchit http://home.chpc.utah.edu/~u6000771/batchit
chmod +x /usr/bin/batchit
pip install -U awscli

echo Hello world batchit worked