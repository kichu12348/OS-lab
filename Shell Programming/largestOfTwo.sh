read -p "Enter number 1: " num1
read -p "Enter number 2: " num2

if [ $num1 -gt $num2 ]; then
    echo "$num1 is greater than $num2"
elif [ $num1 -lt $num2 ]; then
    echo "$num2 is greater than $num1"
else
    echo "$num1 is equal to $num2"
fi