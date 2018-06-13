#include<fcntl.h>


main(int argc, char* argv[]){

  int stdin = 0;
  int stdout = 1;
  int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
  
  int read_bytes;
  char buffer[1024];
  
  while(read_bytes=read(stdin, buffer, 1024)){
     write(stdout, buffer, read_bytes);
     write(fd, buffer, read_bytes);
  }
  close(fd);

return 0;
}
