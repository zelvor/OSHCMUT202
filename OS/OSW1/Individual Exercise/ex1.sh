echo "Input your name: "
read name
if [ ! -n "$name" ] 
then
echo "Null input"
else
echo "Your name = $name"
echo "$name" >> ex1.txt
fi 
