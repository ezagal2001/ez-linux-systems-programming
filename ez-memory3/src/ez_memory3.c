#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{

    size_t pg = sysconf(_SC_PAGESIZE);
    size_t sz = 3 * pg;
    int ret = 0;
    void *ptr;
    char *arr[] = { 
        "yes!", "no",
    };

    /* get memory that is on a page-aligned boundary with posix_memalign(). */
    ret = posix_memalign(&ptr, pg, sz);
    if (ret) {
        fprintf(stderr, "posix_memalgin() failed, exiting now\n");
        exit(EXIT_FAILURE);
    }

    /* initialize the memory! */
    memset(ptr, 'E', sz);

    /* page aligned? */
    unsigned int x = (uintptr_t)ptr % pg; 
    fprintf(stdout, "address: %p, page aligned?: %s\n",
            ptr, (x == 0) ? arr[0] : arr[1]);
   
    /* some of the flags for mlockall():
     * MCL_CURRENT
     * MCL_FUTURE
     * MCL_ONFAULT
     * MCL_FUTURE
     */
    int flags = 0;
    flags |= MCL_CURRENT | MCL_FUTURE;
    ret = mlockall(flags);
    if (ret) {
        fprintf(stderr, "mlock() failed, exiting now.\n");
        free(ptr);
        exit(EXIT_FAILURE);
    }
    /* all memory in this process's vas is "locked" in RAM now! */
    
    /* display memory locked via  grep */
    char *cmd = malloc(256);
    snprintf(cmd, 256 -1, "grep Lck /proc/%d/status", getpid());
    /* run cli command: */
    system(cmd);
    free(cmd);

    sleep(3); 
    /* unlock the memory, now it can be swapped. */
    ret = munlockall();
    if (ret) {
        fprintf(stderr, "munlock() failed, exiting now\n");
        free(ptr);
        exit(EXIT_SUCCESS);
    }

    /* free the memory! */
    free(ptr);

    return EXIT_SUCCESS;
}
