#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        sleep(1);
        printf("Child read from shared memory: %s\n", str);
        shmdt(str);
    } else {
        strcpy(str, "Hello Shared Memory!");
        printf("Parent wrote to shared memory.\n");
        shmdt(str);
    }

    return 0;
}
