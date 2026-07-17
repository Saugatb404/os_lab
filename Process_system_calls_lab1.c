#include <stdio.h>      // printf()
#include <stdlib.h>     // exit() , malloc() , free()
#include <sys/types.h>  //  defines a special system datatype like size_t , pid_t data type
#include <unistd.h>     // fork(), getpid(), execl()
#include <sys/wait.h>   // wait()

int main()
{
    pid_t pid;

    // Get current process ID
    pid = getpid();

    printf("Before fork, Process ID = %d\n", pid);

    // Create child process
    pid = fork();

    if (pid == 0)
    {
        printf("\nThis line is from child.\n");
        printf("Child Process ID = %d\n", getpid());
    }
    else if (pid > 0)
    {
        printf("This line is from parent.\n");
        printf("Child PID returned by fork = %d\n", pid);
    }
    else if (pid < 0)
    {
        printf("\nFork failed.\n");
        exit(1);
    }

    // Child executes ls command
    if (pid == 0)
    {
        execl("/bin/ls", "ls", "-l", (char *)0);  
    }

    // Parent waits for child
    if (pid > 0)
    {
        wait((int *)0);
    }


    return 0;[[]]
}