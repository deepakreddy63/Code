#! /bin/sh
# A simple script to add two numbers

sum()
{
	a=$1
	b=$2
	c=$(($a+$b))
	return $c
}

sum_read()
{
	read -p "Enter first num: " num1
	read -p "Enter second num: " num2

	sum=$(($num1+$num2))

	echo "sum is $sum"
}
echo ' Options to run sum fn 
	1. By entering arguments with sum 
	2. By reading arguments with sum_read '

sum 10 20
echo "sum is $?"


