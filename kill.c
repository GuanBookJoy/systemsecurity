#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    if (argc != 2) return -1;
    printf("kill所有server进程\n");
    execlp("/bin/kill", "/bin/kill", "-9", argv[1], NULL);
    return 0;
}
