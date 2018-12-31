#include <stdio.h>
#include <unistd.h>
main()
{
        int     fd[2];
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        if(fork() == 0)
        {
                close(fd[0]);
		close(1);
                dup(fd[1]);
                execlp("date", "date", NULL);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
}

