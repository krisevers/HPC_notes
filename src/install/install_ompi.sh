######################################
#
#   INSTALL MPI
# 
#   1. install system dependencies
#   2. download OpenMPI
#   4. install OpenMPI
# 
#   @krisevers
#
######################################

echo "Installing system dependencies..."
sudo apt-get update && sudo apt-get install -y \
    g++ \
    make

# cd ~

MAJOR=5.0
MINOR=8
VERSION=5.0.8
wget https://download.open-mpi.org/release/open-mpi/v${MAJOR}/openmpi-${MAJOR}.${MINOR}.tar.gz
sudo tar -xzvf openmpi-${MAJOR}.${MINOR}.tar.gz
cd openmpi-${MAJOR}.${MINOR}
./configure --prefix=/usr/local
make all install
sudo apt-get install openmpi-bin libopenmpi-dev

cd ..
rm -rf openmpi-${MAJOR}.${MINOR}
rm openmpi-${MAJOR}.${MINOR}.tar.gz