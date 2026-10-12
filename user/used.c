#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  uint64 mem = getusedmem();

  printf("Used memory: %lu bytes\n", mem);
  exit(0);
}