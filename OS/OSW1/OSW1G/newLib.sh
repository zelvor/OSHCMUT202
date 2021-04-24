#!/bin/bash 

#Function to clearly list directories in PATH 
addEntry()
{
        BOOK=("${!1}")
	author=("${!2}")
	year=("${!3}")
        echo "book size ${#BOOK[@]}"
	size=${#BOOK[@]}
        echo "Enter Book's name"
	read newbook
	echo "Enter author"
	read newauthor
	echo "Enter year"
	read newyear
        if [ $size -eq 0 ]
	then
		echo "size = 0"
		BOOK[0]="$newbook"
		author[0]="$newauthor"
		year[0]="$newyear"
		return 0
	fi
        echo "size over 0"
	i=0
	flag=0
	while [[ "$i" -lt "$size" ]]
	do
		if [ "${BOOK[$i]}" = "$newbook" -a "${author[$i]}" = "$newauthor" ]
		then
			if [ ${year[$i]} -eq $newyear ] 
			then
				echo "BOOK is already"
				flag=1
				break 1
			fi
		fi
		i=`expr $i+1`
	done

        echo "flag = : $flag"
	if [ $flag -eq 0 ]
	then
		#BOOK[$size]=$newbook
		#author[$size]=$newauthor
		#year[$size]=$newyear
                echo "$newbook" >> "data.txt"
                echo "$newauthor" >> "data.txt"
                echo "$newyear" >> "data.txt"
	fi
}
searchBook()
{
	flag=0
	BOOK=("${!1}")
	author=("${!2}")
	year=("${!3}")
        size=${#BOOK[@]}
	echo "Enter Book's name "
	read newbook
	echo "Enter author "
	read newauthor
	echo "Enter year "
	read newyear
	if [ $size -eq 0 ]
	then
		echo "There are no books in the library"
		return 0
	fi
	i=0
	flag=0
	while [[ "$i" -lt "$size" ]]
	do
		if [ "${BOOK[$i]}" == "$newbook" -a "${author[$i]}" == "$newauthor" ]
		then
			if [ ${year[$i]} -eq $newyear ] 
			then
				echo "Have this book in the library"
				flag=1
				return 0
			fi
		fi
		i=`expr $i+1`
	done
	if [ $flag -eq 1 ]
	then
		echo "Not Found"
	fi
}
removeEntry()
{
        flag=0
	BOOK=("${!1}")
	author=("${!2}")
	year=("${!3}")
        size=${#BOOK[@]}
	echo "Enter Book's name "
	read newbook
	echo "Enter author "
	read newauthor
	echo "Enter year "
	read newyear
	if [ $size -eq 0 ]
	then
		echo "There are no books in the library"
		return 0
	fi
	i=0
	flag=0
	while [[ "$i" -lt "$size" ]]
	do
		if [ "${BOOK[$i]}" = "$newbook" -a "${author[$i]}" = "$newauthor" ]
		then
			if [ ${year[$i]} -eq $newyear ] 
			then
                                head=$((i*3))
                                tail=$((head +2))
                                sed -i "${head},${tail}d" data.txt
				flag=1
				echo "Removed the book from the library"
				return 0
			fi
		fi
		i=`expr $i+1`
	done
	if [ $flag -eq 1 ]
	then
		echo "Not Found"
	fi
}
