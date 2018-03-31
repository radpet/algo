c=`ps aux | grep -w "man" | wc -l` && echo `expr $c - 1`
