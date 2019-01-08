#include<stdio.h>

int main(){
  //execlp("ls", "ls", "-l", NULL);
    char *argv[3];
    argv[0] = "ls";
    argv[1] = "-la";
    argv[2] = NULL;
    execvp("ls", argv);
}
