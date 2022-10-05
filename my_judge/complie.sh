#!/bin/bash

problemName=$1
path="../problems/${problemName}/${problemName}"
pathc="$path.c"
pathcc="$path.cc"
pathcpp="$path.cpp"

patherror="../problems/$problemName/error.info"
touch patherror
gcc -o $path $pathc &>$patherror||g++ -o $path $pathcc &>$patherror||g++ -o $path $pathcpp &>$patherror