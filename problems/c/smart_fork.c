//
// Created by radoslav on 09.06.18.
//

#include<stdio.h>
#include<stdlib.h>

main(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        int pid = fork();
        printf("forking and pid %d\n", pid);
        if (pid) {
            int status;
            waitpid(pid, &status, 0);
            if (status == 0) {
                printf("status of %d is 0\n", pid);
            } else {
                printf("status of %d is %d\n", pid, status);
                return -1;
            }
        } else {
            printf("executing argv%d %s\n", i, argv[i]);
            execlp(argv[i], argv[i], (char *) NULL);
            printf("error happened\n");
            return -1;
        }
    }

    return 0;
}
