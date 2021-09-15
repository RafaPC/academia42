#!/bin/bash
file=$1
$(./replace $file frog CRAB)
$(sed 's/frog/CRAB/g' $file > $file.sed)
$(diff $file.replace $file.sed)