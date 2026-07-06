/* This program queries the resource limits on the system
 * and writes them to stdout.
 */
#define _GNU_SOURCE /* always define this macro for systems programming? */
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

/* We enclose the macro's arguments with parantheses to
 * ensure correct precedent behavior.
 */
#define ARRAY_LEN(arr) (sizeof((arr)) / sizeof((arr)[0]))

/* This is the fn() that will query the systsm for its resource limits */
int query_system_resources(void)
{

    int ret = 0;
    struct rlimit rlim;
    struct rlim_pair {
        int rlim;
        char *name;
    };

    struct rlim_pair rlim_arr[] = {
        { RLIMIT_CORE, "RLIMIT_CORE" },
        { RLIMIT_DATA, "RLIMIT_DATA" },
        { RLIMIT_NICE, "RLIMIT_NICE" },
        { RLIMIT_FSIZE, "RLIMIT_FSIZE" },
        { RLIMIT_SIGPENDING, "RLIMIT_SIGPENDING" },
        { RLIMIT_MEMLOCK, "RLIMIT_MEMLOCK" },
        { RLIMIT_NOFILE, "RLIMIT_NOFILE" },
        { RLIMIT_MSGQUEUE, "RLIMIT_MSGQUEUE" },
        { RLIMIT_RTTIME, "RLIMIT_RTTIME" },
        { RLIMIT_STACK, "RLIMIT_STACK" },
        { RLIMIT_CPU, "RLIMIT_CPU" },
        { RLIMIT_NPROC, "RLIMIT_NPROC" },
        { RLIMIT_AS, "RLIMIT_AS" },
        { RLIMIT_LOCKS, "RLIMIT_LOCKS" },
    };
    
    char tmp1[16];
    char tmp2[16];

    /* The system call we will use:
     * int prlimit(pid_t pid, int resource,
     *              const struct rlimit *new, struct rlimit *old_limit);
     *
     * The rlimit struct definition:
     * struct rlimit {
     *      rlim_t rlim_cur; soft limit
     *      rlim_t rlim_max; hard limit
     * }
     */
    printf("RESOURCE LIMIT      \tSOFT      \tHARD\n");
    int i;
    for (i = 0; i < ARRAY_LEN(rlim_arr); i++) {
        ret = prlimit(0, rlim_arr[i].rlim, 0, &rlim);
        if (ret) {
            return ret;
        }
        snprintf(tmp1, 16, "%ld", rlim.rlim_cur);
        snprintf(tmp2, 16, "%ld", rlim.rlim_max);
        printf("%-18s: %16s %16s\n",
                rlim_arr[i].name,
                (rlim.rlim_cur == -1 ? "unlimited" : tmp1),
                (rlim.rlim_max == -1 ? "unlimited" : tmp2)
              );
    }

    return ret;
}

int main(int argc, char *argv[])
{
    int ret = 0;

    /* Querying the systems resources now. */
    ret = query_system_resources();
    if (ret) {
        printf("The query_system_resources() failed, exiting "
                "now...\n");
        return EXIT_FAILURE;
    }

    printf("Program has ended.\n");

    return EXIT_SUCCESS;
}
