echo "Enter a number: "
read n
i=0
j=0
while [ $i -le ` expr $n - 1` ]
do 
	j=0
	while [ $j -le ` expr $n - 1` ]
	do
		if [ ` expr $n - 1` -le `expr $i + $j` ]
		then 
			echo -n "*"
		else
			echo -n " "
		fi
		j=$((j + 1))
	done
	echo
	i=$((i+1))
done
