#include <stdio.h>      // printf(), getchar()
#include <fcntl.h>      // open(), O_RDONLY, O_RDWR, O_CREAT, O_TRUNC
#include <unistd.h>     // read(), write(), close()
#include <sys/types.h>  // System data types like ssize_t
#include <sys/stat.h>   // File permission constants

int main()
{
    int n;
    int i = 0;

    int f1, f2;

    char c;
    char strin[100];

    // Create or open file for reading and writing
    // If file exists, erase previous contents
    f1 = open("data", O_RDWR | O_CREAT | O_TRUNC, 0644);

    printf("Enter a string: ");

    // Read characters from keyboard until Enter is pressed
    while ((c = getchar()) != '\n')
    {
        strin[i++] = c;
    }

    // Add string terminator
    strin[i] = '\0';

    // Write string into file
    write(f1, strin, i);

    // Close first file
    close(f1);

    // Open file for reading
    f2 = open("data", O_RDONLY);

    // Read data from file
    n = read(f2, strin, sizeof(strin) - 1);

    // Add null character
    strin[n] = '\0';

    printf("\nData from file: %s\n", strin);

    close(f2);

    return 0;
}