#!/bin/bash
######################################
#
#   INSTALL HDF5
# 
#   1. install system dependencies
#   2. download hdf5
#   4. install hdf5
#
#   Usage: ./install_hdf5.sh [--parallel] [--prefix=/path/to/install]
# 
#   @krisevers
#
######################################

# Update packages and install prerequisites
sudo apt-get update
sudo apt-get install -y build-essential openmpi-bin libopenmpi-dev wget

# Download the latest HDF5 release (edit version as needed)
HDF5_VERSION=1.14.3
wget https://github.com/HDFGroup/hdf5/archive/refs/tags/hdf5-$HDF5_VERSION.tar.gz
tar -xzvf hdf5-hdf5-$HDF5_VERSION.tar.gz
cd hdf5-hdf5-$HDF5_VERSION

# Configure with MPI support
./configure --enable-parallel --prefix=/usr/local/hdf5-parallel CC=mpicc

# Build and install
make -j$(nproc)
sudo make install

# Add HDF5 binaries and libraries to your environment (add this to your ~/.bashrc)
export PATH=/usr/local/hdf5-parallel/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/hdf5-parallel/lib:$LD_LIBRARY_PATH

# Verify installation
mpicc -show
h5pcc -showconfig