echo "Enter a number: "
read n
i=1
a=0
while [ $i -ne $n ]
do
	a=$(($a+$i))
	i=`expr $i + 1`
done
a=$(($a+$i))
echo "Sum is $a"

avg=$(($a/$n))
echo "Average is $avg"
