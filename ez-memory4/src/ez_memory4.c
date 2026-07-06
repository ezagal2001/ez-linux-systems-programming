/* program that uses memprotect() on specific pages on virtual
 * memory.
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>

struct ez_data {
    int x;
    int y;
    int j;

    char name[256];
};

typedef unsigned long long u64;
int test_ezmem(u64 addr)
{
    size_t max = 3000; 
    //snprintf((void *)addr, max, "writing to the memory");
    memset((void *)addr, 'w', max);    

    return 0;

}

int main(int argc, char *argv[])
{

    size_t pgsz = sysconf(_SC_PAGESIZE);
    size_t sz = 4 * pgsz;
    int ret = 0;
    void *ptr;
    char *arr[] = { 
        "yes!", "no",
    };

    /* get memory that is on a page-aligned boundary with posix_memalign(). */
    ret = posix_memalign(&ptr, pgsz, sz);
    if (ret) {
        fprintf(stderr, "posix_memalgin() failed, exiting now\n");
        exit(EXIT_FAILURE);
    }

    /* initialize the memory! */

    /* page aligned? */
    unsigned int x = (u64)ptr % pgsz; 
    fprintf(stdout, "address: %p, page aligned?: %s\n",
            ptr, (x == 0) ? arr[0] : arr[1]);
   
    /* set up an array of memory protections we will use in the 
     * for statement to set up protections for each page(total of 4)
     * that we have allocated.
     */

    //ret = mprotect(ptr, pgsz, j);
    if (ret) {
        fprintf(stdout, "mprotect() failed\n");
        free(ptr);
        exit(EXIT_FAILURE);
    }

    struct ez_data *ezptr = (struct ez_data *)ptr; 
    /* initialize the memory */
    memset(ezptr, 0, sz);
    printf("The size of the struct ez_data is: %lu bytes, "
            "there are %lu members per page, page size is: %zu\n",
                sizeof(struct ez_data), pgsz / sizeof(struct ez_data), pgsz);

    int prot[] = {PROT_READ | PROT_WRITE, PROT_NONE, PROT_WRITE | PROT_READ, PROT_NONE,};
    u64 start;
    int i;
    for (i = 0; i < 4; i++) {
        start = (u64)ptr + (i * pgsz);
        ret = mprotect((void *)start, pgsz, prot[i]);
    }

    ezptr[46].x = 7;
    printf("%d\n", ezptr[46].x);
    /* free the memory! */
    free(ptr);

    return EXIT_SUCCESS;
}
