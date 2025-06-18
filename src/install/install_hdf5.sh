#!/bin/bash
######################################
#
#   INSTALL HDF5
# 
#   1. install system dependencies
#   2. download hdf5
#   4. install hdf5
#
#   Usage: ./install_hdf5.sh [--parallel]
# 
#   @krisevers
#
######################################

# Update packages and install prerequisites
sudo apt-get update
sudo apt-get install -y build-essential openmpi-bin libopenmpi-dev wget

# Download the latest HDF5 release
git clone https://github.com/HDFGroup/hdf5.git
cd hdf5

# Configure with MPI support
if [[ "$1" == "--parallel" ]]; then
    cmake -DHDF5_ENABLE_PARALLEL=ON -DHDF5_BUILD_CPP_LIB=ON -DHDF5_ALLOW_UNSUPPORTED=ON ..
else
    cmake -DHDF5_BUILD_CPP_LIB=ON -DHDF5_ALLOW_UNSUPPORTED=ON ..
fi
cmake --build .
sudo make install