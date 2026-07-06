#include "../include/ez_fio.h"

int ezfio1(const char *pname, const char *m)
{
    /* fopen() << perform i/o >> fclose() */
    
    /* Lets open the file */
    FILE *strm;
    strm = fopen(pname, m);

    /* Lets write to the file we just opened */
    fprintf(strm, "I can overcome!\n");
    
    /* ANSI standard requires us to explicitely set the 
     * seek position in between read/write operations on a
     * stream.
     */
    long os = 1;
    ez_set_seek(strm, os, SEEK_END);

    fprintf(stdout, "About to leave ezfio1!\n");
    /* We have to close the stream */
    fclose(strm); 
    
    return 0;
}

int ez_set_seek(FILE *stream, long offset, int whence)
{
    /* set the seek position within the file stream */

    /* whence macros: SEEK_SET, SEEK_CURR, SEEK_END */
    int ret = fseek(stream, offset, whence);

    return ret;
}

long ez_tell_seek(FILE *stream)
{
    /* returns the seek position of the file stream */

    long ret = ftell(stream);

    return ret;
}

void ez_rewind_seek(FILE *stream)
{
    /* rewinds the seek position to byte 0 of the file stream */
    rewind(stream);
}

