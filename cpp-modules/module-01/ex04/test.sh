#!/bin/bash

$(./replace file.txt hola adios)
$(clang++ main_stdreplace.cpp -o std_replace)
$(cp file.txt file2.txt)
$(./std_replace file2.txt hola adios)
$(diff file.txt.replace file2.txt.replace)