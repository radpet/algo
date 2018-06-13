#include<fcntl.h>

main(int argc, char* argv[]){
  
  int stdin = 0;
  
  int read_bytes;
  char buffer[1024];
  int fd = open(argv[1], O_WRONLY | O_CREAT , 0777);
  while(read_bytes=read(1, buffer, 1024)){
    write(fd, buffer, read_bytes);
  }

  close(fd);
  

return 0;
}
