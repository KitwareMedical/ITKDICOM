#!/bin/sh

script_dir="`cd $(dirname $0); pwd`"

docker run \
  --rm \
  -v $script_dir/../..:/ITKDICOM \
    insighttoolkit/dicom-test \
      /ITKDICOM/test/Docker/test.sh
