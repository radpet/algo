#include<fcntl.h>
#include<stdio.h>

main(){

int fd = open("file_no_race.txt", O_WRONLY| O_CREAT| O_TRUNC, 0777);

printf("opening fd=%d\n", fd);

int pid = fork();

if(pid){

  waitpid(pid,0);
  int pid2 = fork();
  if(pid2){
   
  }else{
   printf("writing bar to fd=%d\n",fd);
   int barwrite = write(fd, "bar\n", 4);
   if(barwrite == -1) printf("error writing bar\n");
   close(fd);
   printf("closed fd=%d\n", fd);
  }

}else{
  printf("writing foo to fd=%d\n",fd);
  int writefoo = write(fd, "foo\n",4);
  if(writefoo ==-1) printf("error writing foo\n"); 
}



return 0;

}
