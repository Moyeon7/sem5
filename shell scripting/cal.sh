echo "Enter principle amount: "
read p
echo "Enter rate of interest: "
read r
echo "Enter the time period: "
read n
product=$(($p*$r*$n))
si=$(($product/100))
echo "Simple Interest is $si"
