Zrythm is a free modern music production system, also known as DAW.
It uses the GTK+3 toolkit.

To compile

First compile libdazzle in ext (follow directions there)
Then,
```
autoreconf --install
mkdir build
cd build
../configure
make
```

To install
```
sudo make install
```
