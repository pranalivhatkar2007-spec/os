
#!/bin/bash

while true
do
echo "1.Create 2.View 3.Insert"
echo "4.Delete 5.Exit"

read -p "Enter choice: " ch

case $ch in

1)
touch address.txt
echo "Created"
;;

2)
cat address.txt
;;

3)
read -p "Enter ID Name Phone: " id name phone
echo "$id $name $phone" >> address.txt
echo "Inserted"
;;

4)
read -p "Enter ID: " id
grep -v "^$id " address.txt > temp.txt
mv temp.txt address.txt
echo "Deleted"
;;

5)
exit
;;

*)
echo "Wrong choice"
;;

esac
done

0/p command 

chmod +x p1_address_book.sh
./p1_address_book.sh