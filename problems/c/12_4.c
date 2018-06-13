#include<fcntl.h>

main(int argc, char* argv[]){
  int stdout = 1;
  char buffer[1024];
  for(int i=1;i<argc; i++){
    int fd = open(argv[i], O_RDONLY, 0777);
    if(fd !=-1){
      int read_bytes;
      while(read_bytes=read(fd, buffer, 1024)){
        write(stdout, buffer, read_bytes);
      }
      close(fd);
    }
  }
  
  return 0;
}
