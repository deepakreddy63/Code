#! /bin/sh

# shell script to perform following operations on any code file
# uses grep and sed commands
echo "Options: 
	1. print all lines having a particular keyword eg:int
		eg: code_editor.sh 1 int file
	2. print all lines starting with a keyword eg:#
		eg: code_editor.sh 2 # file
	3. print all lines ending with ;
		eg: code_editor.sh 3 file
	4. Count number of blank lines
		eg: code_editor.sh 4 file
	5. Replace occurences of an identifier with other eg: val by var
		eg: code_editor.sh val var file "

echo ""
echo "Command format -> . code_editor.sh option_num args file"
if [ $# -lt 2 ]
then 
	echo "Not enough arguments. Only $# ($*) provided"
	echo "Follow command format shown above"
	return 1
fi

if [ $1 == 1 ]
then
	echo " printing all lines having $2"
	grep -wn $2 $3
elif [ $1 == 2 ]
then
	echo " printing all lines starting with $2"
	grep -n "^$2" $3
elif [ $1 == 3 ]
then
	echo " printing all lines ending with ; in $2"
	grep -n "\;$" $2
elif [ $1 == 4 ]	
then
	echo " counting number of blank lines in $2"
	grep -c "^$" $2
elif [ $1 == 5 ]
then
	echo " replace occurences of $2 with $3 in $4"
	#/g is kept as global and replaces all occurences instead of just first occurence in line
	sed "s/$2/$3/g" <$4
else
	echo " Program doesn't support this option"
fi
