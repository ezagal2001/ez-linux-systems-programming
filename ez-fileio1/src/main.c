#include "../include/ez_fio.h"

int main(void)
{
    /* File to open and the mode */
    char *path = "ezfile.txt";

    /* append mode, I think. */
    char *mode = "a";
    
    int r = ezfio1(path, mode);

    return EXIT_SUCCESS;
}
