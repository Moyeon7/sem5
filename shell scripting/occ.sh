echo "Enter a string: "
read w

echo "Enter the character whose count you need: "
read c

printf "Count is "
echo $w | grep -o "$c" | wc -l
