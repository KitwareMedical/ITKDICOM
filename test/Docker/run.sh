#!/bin/sh

script_dir="`cd $(dirname $0); pwd`"

docker run \
  --rm \
  -v $script_dir/../..:/usr/src/ITKDICOM \
    insighttoolkit/dicom-test \
      /usr/src/ITKDICOM/test/Docker/test.sh
