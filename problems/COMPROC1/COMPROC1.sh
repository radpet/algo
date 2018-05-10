br=0
br=`expr $3 + $br`
set 5 7 9
shift
echo $?
for var
do
if test $br -lt $var
 then br=`expr $br \* $2`
 echo $br $2 > fout
 else br=`expr $1 \* $br`
   echo $br $1 > fout
 fi
 echo $3
 done
 cat fout
