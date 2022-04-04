#include <stdio.h>
#include <threads.h>

int run(void *arg)
{
    printf("Hello world of C11 threads.");

    return 0;
}

int main(void)
{
    thrd_t thread;
    int result;

    thrd_create(&thread, run, NULL);

    thrd_join(thread, &result);

    printf("Thread return %d at the end\n", result);
}