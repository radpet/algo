#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#define IN 0
#define OUT 1 
int main(int argc, char *argv[]){
 int fd[2];
  pipe(fd);

  if(fork() != 0){
    close(fd[OUT]);
    char buffer[1024];
    int rc = read(fd[IN], buffer, 1024);
    write(OUT, buffer, rc);
  }else{
    close(fd[IN]);
    dup2(fd[OUT], OUT);
    close(fd[OUT]);
    write(OUT, "bye\n", 5);
  }

}
