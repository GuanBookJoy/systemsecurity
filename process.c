#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int a = 0;
    while (1)
    {
        printf("%d\n", a++);
        sleep(5);
    }
    return 0;
}
