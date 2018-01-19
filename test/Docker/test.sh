#!/bin/bash

# This is a script to build the modules and run the test suite in the base
# Docker container.

set -x
set -o

cd /ITKDICOM
branch=$(git rev-parse --abbrev-ref HEAD)
date=$(date +%F_%H_%M_%S)
sha=$(git rev-parse --short HEAD)

cd /ITKDICOM-build
curl -L https://raw.githubusercontent.com/InsightSoftwareConsortium/ITK/dashboard/itk_common.cmake -O
SHASNIP=$(echo $sha | cut -c1-7)
cat > dashboard.cmake << EOF
set(CTEST_SITE "Docker")
set(CTEST_BUILD_NAME "External-ITKDICOM-${SHASNIP}")
set(CTEST_BUILD_CONFIGURATION "MinSizeRel")
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_BUILD_FLAGS: "-j5")
set(CTEST_SOURCE_DIRECTORY /ITKDICOM)
set(CTEST_BINARY_DIRECTORY /ITKDICOM-build)
set(dashboard_model Experimental)
set(dashboard_no_clean 1)
set(dashboard_no_update 1)
set(dashboard_cache "
ITK_DIR:PATH=/ITK-build
BUILD_TESTING:BOOL=ON
")
include(\${CTEST_SCRIPT_DIRECTORY}/itk_common.cmake)
EOF
ctest -j 2 -E KWStyle -VV -S dashboard.cmake
