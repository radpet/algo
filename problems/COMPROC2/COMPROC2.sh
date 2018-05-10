br=0
br=`expr $br + $2`
set 3 5 7
shift
for var
do
if test $br -lt $2
  then br=`expr $br \* $2`
    echo $br $2 >> file
    true
  else br=`expr $1 \* $br`
    echo $br $1 >> file
    false
  fi
  echo $?
done
cat file
