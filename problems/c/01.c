//
// Created by radoslav on 06.11.18.
//

#include<stdio.h>
#include <unistd.h>

int main() {
    int STDOUT = 1;
    char msg[124] = "";
    int childPid = fork();
    if (childPid == 0) {
        sleep(5);
        sprintf(msg, "Spawned; Pid=%d and PPid=%d\n", getpid(), getppid());
    } else {
        int returnStatus;
        waitpid(childPid, &returnStatus, 0);

        sprintf(msg, "Main process; Pid=%d and PPid=%d\n", getpid(), getppid());
    }
    write(STDOUT, msg, sizeof(msg));
}