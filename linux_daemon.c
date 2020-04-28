
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>


static bool foreground = false;


void fatal(char *fmt, ...)
{
    char buf[128];
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    fprintf(stderr, "%s\n", buf);

    fflush(stderr);

    exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{

    pid_t pid;

    if(!foreground) {
        /* Fork off the parent process */

        pid = fork();

        if (pid < 0) { exit(EXIT_FAILURE); }

        /* If we got a good PID, then we can exit the parent process. */

        if (pid > 0) { exit(EXIT_SUCCESS); }

        /* Change the file mode mask */

        umask(0);

        /* Open any logs here */

        /* NONE */

        /*  Create a new SID for the child process */

        if (setsid() < 0) fatal("setsid failed (%m)");

        /* Change the current working directory */

        if ((chdir("/")) < 0) fatal("chdir failed (%m)");

        /* Close out the standard file descriptors */

        fclose(stdin);
        fclose(stdout);
    }

    return 0;
}