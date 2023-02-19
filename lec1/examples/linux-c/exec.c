#include<stdio.h>
#include<string.h>
#include<unistd.h>
int
main()
{
  char *argv[] = { "echo", "this", "is", "echo", 0 };
  execv("./echo", argv);
  printf("exec failed!\n");
}