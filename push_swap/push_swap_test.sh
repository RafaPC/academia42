#!/bin/bash

echo "Testing with $1 numbers"
counter=0
for i in {1..100}
do
	numbers=$(./a.out $1)
	checker_output=$(./push_swap $numbers | ./checker_linux $numbers)
	if [[ $checker_output != "OK" ]]; then
		echo "Error with the numbers $numbers"
	fi
	current_instruc=$(./push_swap $numbers | wc -l)
	counter=$(($counter + $current_instruc))
done
echo "100 tests performed con $1 numbers on an average of $(($counter / 100)) instructions"