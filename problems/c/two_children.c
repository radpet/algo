#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>


main(int argc, char* argv[]){

  int pid = fork();

  if(pid){
    printf("spawned 1 pid=%d\n",pid);
    int pid2 = fork();
    if(pid2){
      printf("spawned 2 pid=%d\n", pid2);
      int status;
      int fp = wait(&status);
      if(status !=0){
        fp = wait(&status);
        if(status == 0) printf("%d exited successfully\n", fp);
        else return -1;
      }else{
        printf("%d exited successfully\n", fp);
        wait(NULL);
      }
    }
     else{
       execlp(argv[2], argv[2], (char*) NULL);
       return -1;
     }
  }else{
       for(int i=0;i<100000;i++);
       execlp(argv[1], argv[1], (char*) NULL);
       return -1;
  }

  return 0;
}
