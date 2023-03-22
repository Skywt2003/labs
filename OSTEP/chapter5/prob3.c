#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("In child process %d\n", (int)getpid());
        printf("hello\n");
    } else {
        int wc = wait(NULL);
        printf("In parent process %d\n", (int)getpid());
        printf("goodbye\n");
    }
}
