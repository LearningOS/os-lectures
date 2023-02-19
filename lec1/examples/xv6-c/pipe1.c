
// pipe1.c: communication over a pipe

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int fds[2];
  char buf[100];
  int n;

  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);
  
  write(fds[1], "this is pipe1\n", 14);
  n = read(fds[0], buf, sizeof(buf));

  write(1, buf, n);

  exit(0);
}
