file_name=$1
shift

for user_id
do
  tty=`who | sort| cut -d " " -f 2| head -n 1`
  write $user_id $tty < $file_name > /dev/null
  if !(test $? -eq 0)
  then
    echo "Cannot send msg"
  fi
done
