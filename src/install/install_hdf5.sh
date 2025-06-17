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

set -e  # Exit on any error

# Default values
HDF5_VERSION="1.14.6"
PARALLEL=true
PREFIX="/usr/local"
BUILD_DIR="/tmp/hdf5-build-$$"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --parallel)
            PARALLEL=true
            shift
            ;;
        --prefix=*)
            PREFIX="${1#*=}"
            shift
            ;;
        --version=*)
            HDF5_VERSION="${1#*=}"
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo "Options:"
            echo "  --parallel        Enable parallel HDF5 with MPI support"
            echo "  --prefix=PATH     Installation prefix (default: /usr/local)"
            echo "  --version=VER     HDF5 version to install (default: 1.14.3)"
            echo "  -h, --help        Show this help message"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

echo "=== HDF5 Installation Script ==="
echo "Version: $HDF5_VERSION"
echo "Parallel: $PARALLEL"
echo "Prefix: $PREFIX"
echo "Build directory: $BUILD_DIR"
echo

# Check if running as root for system-wide installation
if [[ "$PREFIX" == "/usr/local" ]] && [[ $EUID -ne 0 ]]; then
    echo "Warning: Installing to /usr/local typically requires root privileges."
    echo "You may need to run with sudo or choose a different prefix with --prefix="
    read -p "Continue anyway? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Install dependencies
echo "Installing dependencies..."
if command -v apt-get &> /dev/null; then
    # Debian/Ubuntu
    sudo apt-get update
    sudo apt-get install -y build-essential cmake wget zlib1g-dev
    if [ "$PARALLEL" = true ]; then
        sudo apt-get install -y libopenmpi-dev openmpi-bin
    fi
elif command -v yum &> /dev/null; then
    # RHEL/CentOS/Fedora
    sudo yum groupinstall -y "Development Tools"
    sudo yum install -y cmake wget zlib-devel
    if [ "$PARALLEL" = true ]; then
        sudo yum install -y openmpi-devel
        # Load MPI module if using environment modules
        if command -v module &> /dev/null; then
            module load mpi/openmpi-x86_64 2>/dev/null || true
        fi
    fi
elif command -v brew &> /dev/null; then
    # macOS with Homebrew
    brew install cmake wget
    if [ "$PARALLEL" = true ]; then
        brew install open-mpi
    fi
else
    echo "Package manager not detected. Please install the following manually:"
    echo "- C compiler (gcc/clang)"
    echo "- CMake"
    echo "- wget"
    echo "- zlib development headers"
    if [ "$PARALLEL" = true ]; then
        echo "- MPI implementation (OpenMPI or MPICH)"
    fi
    read -p "Press Enter to continue assuming dependencies are installed..."
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Clone HDF5 source from GitHub
echo "Cloning HDF5 $HDF5_VERSION from GitHub..."
git clone --branch "hdf5-$HDF5_VERSION" --depth 1 https://github.com/HDFGroup/hdf5.git

cd hdf5

# Configure build
echo "Configuring build..."
CONFIG_ARGS="--prefix=$PREFIX --enable-fortran --enable-hl"

if [ "$PARALLEL" = true ]; then
    echo "Configuring for parallel build with MPI..."
    CONFIG_ARGS="$CONFIG_ARGS --enable-parallel"
    
    # Set MPI compilers if available
    if command -v mpicc &> /dev/null; then
        export CC=mpicc
    fi
    if command -v mpicxx &> /dev/null; then
        export CXX=mpicxx
    fi
    if command -v mpifort &> /dev/null; then
        export FC=mpifort
    elif command -v mpif90 &> /dev/null; then
        export FC=mpif90
    fi

    echo "Using compilers: CC=$CC, CXX=$CXX, FC=$FC"
else
    CONFIG_ARGS="$CONFIG_ARGS --enable-cxx"
fi

# Run configure
./configure $CONFIG_ARGS

# Build
echo "Building HDF5..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Test (optional but recommended)
echo "Running tests..."
make check

# Install
echo "Installing HDF5..."
make install

# Update library cache on Linux
if command -v ldconfig &> /dev/null && [[ "$PREFIX" == "/usr/local" ]]; then
    sudo ldconfig
fi

# Cleanup
cd /
rm -rf "$BUILD_DIR"

echo
echo "=== Installation Complete ==="
echo "HDF5 $HDF5_VERSION installed to: $PREFIX"
echo

# Display installation info
echo "Installation details:"
echo "- Headers: $PREFIX/include"
echo "- Libraries: $PREFIX/lib"
echo "- Binaries: $PREFIX/bin"

if [ "$PARALLEL" = true ]; then
    echo "- Parallel support: ENABLED (MPI)"
else
    echo "- Parallel support: DISABLED"
fi

echo
echo "To use HDF5 in your C programs:"
echo "- Include: #include <hdf5.h>"
echo "- Compile: gcc -I$PREFIX/include your_program.c -L$PREFIX/lib -lhdf5"

if [ "$PREFIX" != "/usr/local" ]; then
    echo
    echo "Since you installed to a custom prefix, you may need to:"
    echo "export LD_LIBRARY_PATH=$PREFIX/lib:\$LD_LIBRARY_PATH"
    echo "export PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig:\$PKG_CONFIG_PATH"
fi

echo
echo "Installation successful!"