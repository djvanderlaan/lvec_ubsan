#!/bin/sh

cd pkg1
make clean
make test
make install
cd ..

cd pkg2
make clean
make test
cd ..
