#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* 
    Very important!

    Opening the read or write end of a FIFO blocks until the other
    end is also opened (by another process or thread).  See fifo(7)
    for further details. 
*/

int main(int argc, char* argv[])
{
    if (mkfifo("myfifo1", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    printf("Opening...\n");

    /* Only read! */
    //int fd = open("myfifo1", O_WRONLY);

    /* Read and Write same time! */
    int fd = open("myfifo1", O_RDWR);
    
    printf("Opened\n");
    int x = 97;
    if (write(fd, &x, sizeof(x)) == -1)
    {
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");


    return 0;
}