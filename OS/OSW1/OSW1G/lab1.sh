#!/bin/bash

#include library
. ~/Desktop/OS/OSW1/OSW1G/newLib.sh
i=0
while read line
do
	if [ $((i % 3)) -eq 0 ]
	then
		echo "read book"
		Book[$((i/3))]=$line
	elif [ $((i % 3)) -eq 1 ]
	then
		echo "read author"
		author[$((i/3))]=$line
	else
		echo "read year"
		year[$((i/3))]=$line
	fi
	i=$((i+1))
done < "data.txt"
echo "${Book[2]}"
echo "${author[2]}"
echo "${year[2]}"
over=1
while [ $over != 0 ]
do
	echo "1.Search Book"
	echo "2.Add Entry"
	echo "3.Remove Entry"
	echo "4.Exit"
	read choose
	if [ $choose -eq 4 ]
	then 
		over=0
	elif [ $choose -eq 1 ]
	then
		echo "You choose Search Book  ";
		searchBook Book[@] author[@] year[@]
	elif [ $choose -eq 2 ]
	then
		echo "You choose Add Book  ";
		addEntry Book[@] author[@] year[@] 
	elif [ $choose -eq 3 ]
	then
		echo "You choose Remove Book  ";
		removeEntry Book[@] author[@] year[@]
	fi
done
