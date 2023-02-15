//https://zhuanlan.zhihu.com/p/402341124
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main()
{
    __pid_t pid;
    int fd[2];
    char str[20];
    pipe(fd);
    if ((pid = fork() == 0))
    {
        printf("children\n");
        close(fd[1]);
        int num;
        while ((num = read(fd[0], str, sizeof(str)) != 0))
        {
            printf("read: %s", str);
        }
    }
    else
    {
        printf("parent\n");
        close(fd[0]);
        for (int i = 0; i < 10; i++)
        {
            sprintf(str, "the %d message. \n", i);
            printf("write: %s", str);
            write(fd[1], str, sizeof(str));
        }
    }
}