dir_name=$1

if test -d ~/$dir_name
then
  echo "Exists"
else
  echo "No such dir"
  mkdir ~/$dir_name
fi

br=0
for f in *
do
  if test -r $f
  then
    if test -w $f
    then
      cp $f ~/$dir_name
    else
      br=`expr $br + 1`
    fi
  else
    br=`expr $br + 1`
  fi
done
echo $br
