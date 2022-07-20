#! /bin/sh

cp ../libirprocess/include/libirprocess.h  ./include
cp ../libirparse/include/libirparse.h  ./include
cp ../libiruvc/include/libiruvc.h  ./include
cp ../libircmd/include/libircmd.h  ./include

echo "header file copy to /include directory finished !!!"

cp ../libirprocess/build/libirprocess.so  ./libs
cp ../libirparse/build/libirparse.so  ./libs
cp ../libiruvc/build/libiruvc.so*  ./libs
cp ../libircmd/build/libircmd.so*  ./libs
echo "lib copy to ./libs directory finished !!!"
