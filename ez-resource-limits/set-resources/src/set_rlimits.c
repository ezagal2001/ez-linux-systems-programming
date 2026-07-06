/* This program sets resource limits on the system. The user must send which
 * resource to update via a switch followed by the new value.
 * 
 */
#define _GNU_SOURCE /* always define this macro for systems programming? */
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* We enclose the macro's arguments with parantheses to
 * ensure correct precedent behavior.
 */
#define ARRAY_LEN(arr) (sizeof((arr)) / sizeof((arr)[0]))

struct ez_res {
    char *name;
    rlim_t num;
};

int print_res_switch(void)
{

    char *rlim_arr[] = { 
         "RLIMIT_CORE,    \t\"cor\"",
         "RLIMIT_DATA,    \t\"dat\"",
         "RLIMIT_NICE,    \t\"nic\"",
         "RLIMIT_FSIZE,   \t\"fsi\"",
         "RLIMIT_SIGPENDING, \t\"sig\"",
         "RLIMIT_MEMLOCK, \t\"mem\"",
         "RLIMIT_NOFILE,  \t\"nof\"" ,
         "RLIMIT_MSGQUEUE,\t\"msg\"",
         "RLIMIT_RTTIME,  \t\"rtt\"",
         "RLIMIT_STACK,   \t\"sta\"",
         "RLIMIT_CPU,     \t\"cpu\"" ,
         "RLIMIT_NPROC,   \t\"npr\"",
         "RLIMIT_AS,      \t\"as\"" ,
         "RLIMIT_LOCKS,   \t\"loc\"",
        };

    char *option = "SWITCH"; 
    printf("RESOURCE_LIMIT %15s\n", option);
    long unsigned i;
    for (i = 0; i < ARRAY_LEN(rlim_arr); i++) {
        printf("%s\n", rlim_arr[i]);
    }

    return 0;
}

int process_switch(char *params, int *index, struct ez_res res[], int sz)
{
    int ret = 0;
    int i;
    for (i = 0; i < sz; ++i) {
        if ((strcmp(res[i].name, params) == 0)) {
            *index = i; 
            return ret;
        } else {
            ;
        }
        
    }

    ret = -1;

    return ret;
}

void print_new_old(int pid, char *n, long  nc, long nm, long oc, long om)
{
    printf("pid:%d: %s rlimit [soft, hard], new:[%ld, %ld], old:[%ld, %ld], "
            "-1 = unlimited\n", 
            pid, n, nc, nm, oc, om);

}

int set_resource(int i, int value, int pid, struct ez_res res[])
{
    
    int ret = 0;
    struct rlimit oldlimit;
    struct rlimit newlimit;

    if (value == -1) {
        newlimit.rlim_cur = newlimit.rlim_max = RLIM_INFINITY;
    } else {
        newlimit.rlim_cur = newlimit.rlim_max = (rlim_t)value;
    }
    
    printf("index is %d, value is %d\n", i, value);
    
    ret = prlimit(pid, res[i].num, &newlimit, &oldlimit);
    if (ret == -1) {
        printf("prlimit() failed, exiting now.\n");
        return ret;
    }

    print_new_old(pid, res[i].name, newlimit.rlim_cur, newlimit.rlim_max,
                oldlimit.rlim_cur, oldlimit.rlim_max);
                
    return ret;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int mindex = 0;
    
    if (argc < 4) {
        ret = print_res_switch();
        exit(0);
    }

    struct ez_res rarr[] = {
        {"cor", RLIMIT_CORE},
        {"dat", RLIMIT_DATA},
        {"nic", RLIMIT_NICE},
        {"fsi", RLIMIT_FSIZE},
        {"sig", RLIMIT_SIGPENDING},
        {"mem", RLIMIT_MEMLOCK},
        {"nof", RLIMIT_NOFILE},
        {"msg", RLIMIT_MSGQUEUE},
        {"rtt", RLIMIT_RTTIME},
        {"sta", RLIMIT_STACK},
        {"cpu", RLIMIT_CPU},
        {"npr", RLIMIT_NPROC},
        {"as", RLIMIT_AS},
        {"loc", RLIMIT_LOCKS},
    };

    int pid = atoi(argv[1]);
    int val = atoi(argv[3]); 
    /* error checking here */
    
    int sz = ARRAY_LEN(rarr);

    /* get the correct index for the rarr[] */
    ret = process_switch(argv[2], &mindex, rarr, sz);
    if (ret) {
        printf("process_switch() failed, exiting now\n");
        return EXIT_FAILURE; 
    }

    ret = set_resource(mindex, val, pid, rarr); 

    return EXIT_SUCCESS;
}
