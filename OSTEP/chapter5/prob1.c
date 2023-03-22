#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int x;

int main(int argc, char *argv[])
{
    x = 123;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        x = 456;
        printf("In child process %d, x=%d\n", (int)getpid(), x);
    } else {
        printf("In parent process %d, x=%d\n", (int)getpid(), x);
    }
}
