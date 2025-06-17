git clone https://github.com/dun/munge.git
cd munge
./bootstrap
./configure \
    --prefix=/usr \
    --sysconfdir=/etc \
    --localstatedir=/var \
    --runstatedir=/run
make
make check
sudo make install

cd ..
rm -rf munge