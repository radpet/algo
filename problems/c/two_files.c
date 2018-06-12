
#include<fcntl.h>
#include<stdio.h>

main(){

int fd = open("file_race.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
printf("Opening file fd=%d\n", fd);

  int pid = fork();
  printf("Spawning pid %d\n",pid);
  
  if(pid){//parent
    int pid2 = fork();
    printf("Spawning pid %d\n",pid2);
    if(pid2){
      waitpid(pid, NULL, 0);
      waitpid(pid2, NULL, 0);
      printf("waited for both pid and pid2\n");
      printf("closing fd=%d\n",fd);
      close(fd);
    }else{
      printf("writing bar\n");
      int barwrite= write(fd, "bar\n", 4);
      if(barwrite==-1) printf("error writing bar\n");
    } 
  }else{//chiild
    printf("writing foo\n");
    int foowrite = write(fd, "foo\n", 4);
    if(foowrite==-1) printf("error writing foo\n");
  }


return 0;
}


