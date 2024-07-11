echo "Enter a number: "
read n
i=1
while [ $i -lt $n ]
do
	a=$(($i*$i))
	echo "Square of $i is $a"
	i=`expr $i + 1`
done
