#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char *address = sbrk(100);

  // Ensure memory is allocated and writable.
  *address = 0x12;

  mprotect(address);

  // Uncomment to test writing to a read-only page.
  // *address = 0x34;

  printf("%d", (int)*address);

  munprotect(address);
  *address = 0x56;
  printf("%d", (int)*address);

  exit(0);
}