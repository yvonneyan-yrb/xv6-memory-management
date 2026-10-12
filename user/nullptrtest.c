#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // Obtain the address at runtime; default to zero.
  uint64 addr = argc > 1 ? (uint64)atoi(argv[1]) : 0;
  volatile char *p = (volatile char *)addr;

  if(argc > 2)
    *p = 1;
  else
    printf("%d\n", (int)*p);

  printf("ERROR: invalid access survived\n");
  exit(1);
}