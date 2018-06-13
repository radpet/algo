#include<fcntl.h>

main(){
  
  int stdin=0;
  int stdout=1;
  
  char buffer[1024];
  int bytes;
  while(bytes=read(stdin, buffer,1024)){
    write(stdout, buffer, bytes);
  }

}
