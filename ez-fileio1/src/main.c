#include "../include/ez_fio.h"

int main(void)
{
    /* File to open and the mode */
    char *path = "ezfile.txt";
    char *mode = "a";
    
    int r = ezfio1(path, mode);

    return EXIT_SUCCESS;
}
