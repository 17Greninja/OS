#!/bin/bash

# # a=(10 9 8 4 5 6 7 3 2 1)

merge() {
	local p1=2
	local p2=$(( $1 + 2 ))
	for i in ${@:2}
	do
		if [[ $p1 -eq $(( $1 + 2 )) ]]
		then
			echo ${@:$p2:1} ; ((p2 += 1))
		else
			if [[ $p2 -eq $(( ${#@} + 1 )) ]]
			then
				echo ${@:$p1:1} ; ((p1 += 1))
			else
				if [[ ${@:$p1:1} -lt ${@:$p2:1} ]]
				then
					echo ${@:$p1:1} ; ((p1 += 1 ))
				else
					echo ${@:$p2:1} ; ((p2 += 1))
				fi
			fi
		fi
	done
}

mergeSort() {
	if [[ $1 -ge 2 ]]
	then
		local med=$(( $1 / 2 ))
		local ptr2=( $(mergeSort $(( $1 - $med )) ${@:$(( $med + 2 )):$(( $1 - $med ))}) )
		local ptr1=( $(mergeSort $med ${@:2:$med}) )
		echo $(merge $med ${ptr1[@]} ${ptr2[@]})
	else
		echo $2
	fi
}

# merge() {
# 	local x=2
# 	local y=$(( $1 + 2 ))
# 	for i in ${@:2}
# 	do
# 		if [[ $x -eq $(( $1 + 2 )) ]]
# 		then
# 			echo ${@:$y:1} ; ((y += 1))
# 		else
# 			if [[ $y -eq $(( ${#@} + 1 )) ]]
# 			then
# 				echo ${@:$x:1} ; ((x += 1))
# 			else
# 				if [[ ${@:$x:1} -lt ${@:$y:1} ]]
# 				then
# 					echo ${@:$x:1} ; ((x += 1))
# 				else
# 					echo ${@:$y:1} ; ((y += 1))
# 				fi
# 			fi
# 		fi
# 	done
# }

# mergesort() {
# 	if [[ $1 -ge 2 ]]
# 	then
# 		local med=$(( $1 / 2 ))
# 		local x=( $(mergesort $med ${@:2:$med}) )
# 		local y=( $(mergesort $(( $1 - $med )) ${@:$(( $med + 2 )):$(( $1 - $med ))}) )
# 		echo $(merge $med ${x[@]} ${y[@]})
# 	else
# 		echo $2
# 	fi
# }

# echo ${a[@]} ; echo $(mergesort 10 ${a[@]})


echo -n "Enter the total number of numbers: "
read n
echo "Enter array elements: "
i=0

while [ $i -lt $n ]
do
    read a[$i]
    i=`expr $i + 1`
done
# echo $n
echo ${a[@]} ; echo $(mergeSort $n ${a[@]})