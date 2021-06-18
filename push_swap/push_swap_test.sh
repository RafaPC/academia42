#!/bin/bash

echo "Probando con $1 números"
counter=0
for i in {1..100}
do
	numbers=$(./a.out $1)
	checker_output=$(./push_swap $numbers | ./checker_linux $numbers)
	if [[ $checker_output != "OK" ]]; then
		echo "Error con la serie $numbers"
	fi
	current_instruc=$(./push_swap $numbers | wc -l)
	counter=$(($counter + $current_instruc))
done
echo "100 pruebas realizadas con $1 números en una media de $(($counter / 100)) instrucciones"