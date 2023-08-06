#!/bin/bash

echo "Enter the string: "
read str

check_lower=0
check_upper=0
check_special=0
check_length=0
check_digit=0
length=${#str}

if [[ $str =~ [A-Z] ]]; then

    check_upper=1
fi
if [[ $str =~ [a-z] ]]; then
    check_lower=1
fi
if [[ $str =~ [0-9] ]]; then
    check_digit=1
fi
if [[ $str =~ ['!@#$%^&*()-+'] ]]; then
    check_special=1
fi
if [ $length -ge 8 ]; then 
    check_length=1
fi

score=$(($check_lower + $check_upper + $check_special + $check_length + $check_digit)) 

if [ $score -eq 5 ]; then 
    echo "Strong Password"
elif [ $check_lower -eq 1 -a $check_upper -eq 1 -a $check_special -eq 1 -a $length -ge 6 ]; then
    echo "Moderate Password"
else
    echo "Weak Password"

fi
