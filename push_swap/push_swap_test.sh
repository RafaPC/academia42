#!/bin/bash

echo "Testing with $1 numbers"
counter=0
biggest_instr_list=0
smallest_instr_list=9999999
for i in {1..100}
do
	numbers=$(./a.out $1)
	checker_output=$(./push_swap $numbers | ./checker_linux $numbers)
	if [[ $checker_output != "OK" ]]; then
		echo "Error with the numbers $numbers"
	fi
	current_instruc=$(./push_swap $numbers | wc -l)
	if (( $current_instruc > $biggest_instr_list )); then
		biggest_instr_list=$current_instruc
	fi
	if (( $current_instruc < $smallest_instr_list )); then
		smallest_instr_list=$current_instruc
	fi
	counter=$(($counter + $current_instruc))
done
echo "100 tests performed with $1 numbers on an average of $(($counter / 100)) instructions"
echo "Biggest result $biggest_instr_list"
echo "Smallest result $smallest_instr_list"