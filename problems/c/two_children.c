#include<stdio.h>


main(int argc, char* argv[]){

  int pid = fork();

  if(pid){
    int pid2 = fork();
    if(pid2){
      int status1;
      int status2;
      while(1){
        waitpid(pid,&status1, 1);
        if(status1 !=-1){
          printf("child 1 exited first with pid=%d\n", pid);
          waitpid(pid2, &status2,0);
          break;
        }
        waitpid(pid,&status2, 1);
        if(status2 !=-1){
         printf("child 2 exited first with pid=%d\n", pid2);
         waitpid(pid, &status1, 0);
         break;
        }
      }
      waitpid(pid,0);
      wait(pid2,0);
    }
     else{
       execlp(argv[2], argv[2], (char*) NULL);
       return -1;
     }
  }else{
       execlp(argv[1], argv[1], (char*) NULL);
       return -1;
  }

  return 0;
}
