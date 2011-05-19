#include <stdio.h>
#include <limits.h>
#include <signal.h>

void
sig_handler(int sig)
{
    printf("Received signal %d\n", sig);
}

int
main()
{
    int a, b, c, d;

    signal(SIGFPE, sig_handler);
    signal(SIGABRT, sig_handler);

//    while (1) {}

    a = b = INT_MAX;
    d = 1;

    c = a + d;

    c = a - b;
    printf("Completed!!!\n");
    return 0;
}
