#!/bin/bash


for file in *
do
    if [ -d $file ]
    then
       echo "clean "$file
        make clean -f $file/Makefile
    fi

done
