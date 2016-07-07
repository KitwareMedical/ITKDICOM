#!/bin/bash

# This is a script to build the modules and run the test suite in the base
# Docker container.

set -x
set -o

cd /usr/src/ITKDICOM
branch=$(git rev-parse --abbrev-ref HEAD)
date=$(date +%F_%H_%M_%S)
sha=$(git rev-parse --short HEAD)

cd /usr/src/ITKDICOM-build
cmake \
  -G Ninja \
  -DITK_DIR:PATH=/usr/src/ITK-build \
  -DCMAKE_BUILD_TYPE:STRING=Release \
  -DBUILDNAME:STRING=External-DICOM-${branch}-${date}-${sha} \
    /usr/src/ITKDICOM
ctest -VV -D Experimental -E KWStyle
