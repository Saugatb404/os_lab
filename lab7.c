#include <stdio.h>     
#include <stdlib.h>   

int main()
{
    FILE *pipe;              // Used to read output from Linux commands
    int option;
    char line[100];

    printf("=================================\n");
    printf(" Demonstration of popen()\n");
    printf("=================================\n");

    printf("1. List Files (ls)\n");
    printf("2. Print Working Directory (pwd)\n");
    printf("3. Display Source File (cat)\n");
    printf("4. Exit\n");

    printf("\nEnter your choice: ");
    scanf("%d", &option);

    switch (option)
    
    {
        //----------------------------------------
        // Execute ls command
        //----------------------------------------
        case 1:

            pipe = popen("ls", "r");  // pipe open creates a direct pipeline (code means exec ls command and give the program a stream from which o/p can be read)


            if (pipe == NULL)
            {
                printf("Error executing ls command.\n");
                return 1;
            }

            printf("\nFiles in Current Directory\n");
            printf("--------------------------\n");

            while (fgets(line, sizeof(line), pipe) != NULL) //Read one line from the command's output through the pipe.
            {
                printf("%s", line);
            }

            pclose(pipe);

            break;

        //----------------------------------------
        // Execute pwd command
        //----------------------------------------
        case 2:

            pipe = popen("pwd", "r");

            if (pipe == NULL)
            {
                printf("Error executing pwd command.\n");
                return 1;
            }

            printf("\nCurrent Working Directory\n");
            printf("-------------------------\n");

            while (fgets(line, sizeof(line), pipe) != NULL)
            {
                printf("%s", line);
            }

            pclose(pipe);

            break;

        //----------------------------------------
        // Execute cat command
        //----------------------------------------
        case 3:

            pipe = popen("cat ch.c", "r");

            if (pipe == NULL)
            {
                printf("Error executing cat command.\n");
                return 1;
            }

            printf("\nContents of ch.c\n");
            printf("-------------------------\n");

            while (fgets(line, sizeof(line), pipe) != NULL)
            {
                printf("%s", line);
            }

            pclose(pipe);

            break;

        //----------------------------------------
        // Exit
        //----------------------------------------
        case 4:

            printf("Program terminated.\n");
            exit(0);

        //----------------------------------------
        // Invalid choice
        //----------------------------------------
        default:

            printf("Invalid choice.\n");
    }

    return 0;
}