/* This program is an exercise in using the memory APIs on the linux os.
 * It prints out various values based on the argument passed at the command line.
 * Running the programming w/o any arguments prints the list of switches to
 * use and what they represent.
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

struct ez1 {
    int i;
    int j;
    int k;
};

void program_help(void)
{
    fprintf(stdout, "This program executes memory related functions.\n" 
            "And prints out some information regarding said functions "
            "and their parameters.\n");
    fprintf(stdout, "option [0] = prints the pagesize for the system to stdout\n"
            "option [1] = prints the address of the current program break\n"
            "option [2] = allocates a page-sized memory using malloc()\n"
            "option [3] = allocates a page-sized memory using calloc()\n"
            "option [4] = uses the realloc() API\n"
            "option [5] = uses the reallocarray() API\n");
}

void print_pagesize(void)
{
    long pgsz1 = sysconf(_SC_PAGESIZE);
    int pgsz2 = getpagesize();
    fprintf(stdout, "sysconf(3): The page size for the system is: %ld bytes\n"
            "getpagesize(2): The page size for the system is: %d bytes\n", pgsz1, pgsz2);
}

void print_programbreak(void)
{
    void *prbreak = sbrk(0); /* current program break: the top of the heap. */
    fprintf(stdout, "The current program break is at address: %p\n", prbreak);
}

int ez_malloc(void)
{
    size_t sz = sysconf(_SC_PAGESIZE);
    void *ptr = malloc(sz);
    if (ptr == NULL) {
        fprintf(stderr, "malloc() failed!\n");
        return -1;
    }
    
    /* initialize the memory! */
    memset(ptr, 0, sz);
    
    fprintf(stdout, "memory was allocated using malloc()!\n"
            "address: %p, size: %zu\n", ptr, sz);

    /* free the memory! */
    free(ptr);
    fprintf(stdout, "memory was freed!\n");

    return 0;
}

int ez_calloc(void)
{
    size_t sz = sizeof(int);
    size_t n = 256; 
    void *ptr = calloc(n, sz);
    if (ptr == NULL) {
        fprintf(stderr, "calloc() failed, exiting now.\n");
        return -1;
    }
    
    /* no need to initialize the memory! the calloc() initializes the memory to
     * ascii 0, not numerical 0.
     */
    fprintf(stdout, "memory was allocated using calloc()!\n"
            "address: %p, size: %zu\n", ptr, (sz * n));

    /* free the memory */
    free(ptr);
    fprintf(stdout, "memory was freed!\n");

    return 0;
}

int ez_realloc(void)
{
    size_t n = 1000;
    size_t newn = 1500;
    size_t sz = n * sizeof(struct ez1); 
    size_t newsz = newn * sizeof(struct ez1);
    void *ptr = NULL;
    void *newptr = NULL;
    
    ptr = malloc(sz);
    if (ptr == NULL) {
        fprintf(stderr, "malloc() failed, exiting now.\n");
        return -1;
    }

    fprintf(stdout, "memory allocated via malloc!\n"
            "address: %p, size: %zu\n", ptr, sz);
    
    /* resize it! */

    /* might the newsz value may overflow, reallocarray()
     * catches this bug, reallocarray() is considered safer.
     */
    newptr = realloc(ptr, newsz);
    if (newptr == NULL) {
        fprintf(stderr, "realloc() failed, exiting now\n");
        free(ptr);
        return -1;
    }
    
    fprintf(stdout, "memory has been resized! using realloc()\n"
            "address: %p, size: %zu\n", newptr, newsz);

    /* free the new ptr not the old ptr! */
    free(newptr);
    
    return 0;
}

int ez_reallocarray(void)
{
    size_t n = 1000;
    size_t newn = 500;
    size_t sz = n * sizeof(struct ez1);
    void *ptr = NULL;
    void *newptr = NULL;

    ptr = malloc(sz);
    if (ptr == NULL) {
        fprintf(stdout, "malloc() failed, exiting now\n");
        return -1;
    }
    
    fprintf(stdout, "memory has been allocated via malloc()!\n"
            "address: %p, size: %zu\n", ptr, sz);

    /* could be used to shrink of grow ptr, using same semantics */
    newptr = reallocarray(ptr, newn, sizeof(struct ez1));
    if (newptr == NULL) {
        fprintf(stderr, "reallocarray() failed, exiting now\n");
        free(ptr);
        return -1;
    }

    fprintf(stdout, "memory has been resized using reallocarry()!\n"
            "address: %p, size: %zu\n", newptr, newn * sizeof(struct ez1));

   /* free the newptr, do not free the old pointer(ptr) */
    free(newptr);

    return 0;
}

int main(int argc, char *argv[])
{
    //fprintf(stdout, "mmap threshold: %d\n", mmap_threshold);
    if (argc < 2) {
        program_help();
        exit(EXIT_SUCCESS);
    }
    int ret = 0; /* initialize here, not within the switch statment */ 
    int cmd = atoi(argv[1]);

    switch (cmd) {
    case 0:
        print_pagesize();
        break;
    case 1:
        print_programbreak();
        break;
    case 2:
        print_programbreak();
        ret = ez_malloc();
        if (ret < 0)
            break;
        print_programbreak();
        break;
    case 3:
        print_programbreak();
        ret = ez_calloc();
        if (ret < 0)
            break;
        print_programbreak();
        break;
    case 4:
        print_programbreak();
        ret = ez_realloc();
        if (ret < 0)
            break;
        print_programbreak();
        break;
    case 5:
        print_programbreak();
        ret = ez_reallocarray();
        if (ret < 0)
            break;
        print_programbreak();
        break;
    default:
        fprintf(stdout, "Invalid argument, please run program "
                " without any argument to see the valid options\n");
        break;
    }

    if (ret < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  
}

