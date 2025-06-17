######################################
#
#   INSTALL SINGULARITY
# 
#   1. install system dependencies
#   2. install golang if necessary
#   3. download singularity
#   4. install singularity
# 
#   @krisevers
#
######################################

echo "Installing system dependencies..."
sudo apt-get update && sudo apt-get install -y \
    autoconf \
    automake \
    cryptsetup \
    fuse2fs \
    git \
    fuse3 \
    libfuse3-dev \
    libseccomp-dev \
    libtool \
    pkg-config \
    runc \
    squashfs-tools \
    squashfs-tools-ng \
    uidmap \
    wget \
    zlib1g-dev \
    libsubid-dev \
    conmon

######################################
if ! command -v go &> /dev/null; then
    echo "Installing go..."
    GO_URL="https://go.dev/dl"
    GO_VERSION=1.24.4
    OS=linux
    ARCH=amd64
    wget ${GO_URL}/go${GO_VERSION}.${OS}-${ARCH}.tar.gz
    sudo tar -C /usr/local -xzvf go${GO_VERSION}.${OS}-${ARCH}.tar.gz
    rm go${GO_VERSION}.${OS}-${ARCH}.tar.gz
    echo "Set the environment variable PATH to point to go..."
    if ! grep -q '/usr/local/go/bin' ~/.bashrc; then
        echo 'export PATH=/usr/local/go/bin:$PATH' >> ~/.bashrc
    fi
    export PATH=/usr/local/go/bin:$PATH
else
    echo "Go is already installed."
fi

######################################
if ! command -v singularity &> /dev/null; then
    echo "Download singularity..."
    git clone --recurse-submodules https://github.com/sylabs/singularity.git
    cd singularity
    ./mconfig --without-libsubid
    make -C builddir
    sudo make -C builddir install
    cd .. && rm -rf singularity
else
    echo "Singularity is already installed."
fi