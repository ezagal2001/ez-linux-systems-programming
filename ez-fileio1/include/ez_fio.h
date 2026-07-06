#ifndef EZ_FIO1_H

#define EZ_FIO1_H

#include "common.h"

int ezfio1(const char *pname, const char *m);
int ez_set_seek(FILE *stream, long offest, int whence);
long ez_tell_seek(FILE *stream);
void ez_rewind_seek(FILE *stream);


#endif
