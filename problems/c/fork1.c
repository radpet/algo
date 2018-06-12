//
// Created by radoslav on 09.06.18.
//
#include<stdio.h>
#include<stdlib.h>

main(int argvc, char *argv[]) {
    int pid = fork();
    printf("spawning first child %d \n", pid);
    if (pid) {
        int status;
        wait(&status);
        printf("status of first child is %d \n", status);
        if (status == 0) {
            printf("%s\n", argv[1]);
            int second = fork();
            printf("spawning second child first is okey %d \n", second);
            if (second) {
                int status2;
                wait(&status2);
                printf("status of second child is %d\n", status2);
                if (status2 == 0) {
                    printf("%s\n", argv[2]);
                } else {
                    printf("error occurred on 2\n");
                    return -1;
                }
            } else {
                printf("executing argv2 \n");
                execlp(argv[2], "");
            }
        } else {
            printf("error occurred on 1 \n");
            return -1;
        }
    } else {
        printf("executing argv1 \n");
        execlp(argv[1], "");
    }

    return 0;
}
