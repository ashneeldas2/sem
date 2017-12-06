#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#define KEY 88380

int main(int argc, char ** argv) {
    if (argc < 2) {
        printf("not enough args\n");
    }
    else if (!strcmp(argv[1], "-c")) {
        int sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
        if (sd == -1) {
            printf("The semaphore already exists!\n");
        }
        else {
            int val;
            sscanf(argv[2], "%d", &val);
            semctl(sd, 0, SETVAL, val);
            printf("semaphore created: %d\n", KEY);
            printf("value set: %d\n", val);
        }
    }
    else if (!strcmp(argv[1], "-v")) {
        int sd = semget(KEY, 0, 0);
        printf("semaphore value: %d\n", semctl(sd, 0, GETVAL));
    }    
    else if (!strcmp(argv[1], "-r")) {
        int sd = semget(KEY, 0, 0);
        printf("semaphore removed: %d\n", semctl(sd, 0, IPC_RMID));
    }
    return 0;
}