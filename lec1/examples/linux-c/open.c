#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int
main()
{
  int fd = open("output.txt", O_WRONLY | O_CREAT);
  write(fd, "ooo\n", 4);
}