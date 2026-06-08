#include "../include/ez_fio.h"

int ezfio1(const char *pname, const char *m)
{
    /* Lets open the file */
    FILE *strm;
    strm = fopen(pname, m);

    /* Lets write to the file we just opened */
    fprintf(strm, "Writing to the local file!\n");
    
    fprintf(stdout, "About to leave ezfio1!\n");

    // check ret later, man ftell() later
    int ret = ftell(strm);

    /* We have to close the stream */
    fclose(strm); 
    
    return 0;
}


