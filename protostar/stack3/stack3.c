#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// address of win: 0x8048424
void win()
{
  printf("code flow successfully changed\n");
}

int main(int argc, char **argv)
{
  volatile int (*fp)();
  char buffer[64];

  fp = 0;

  gets(buffer);

  if(fp) {
      printf("calling function pointer, jumping to 0x%08x\n", fp);
      fp();
  }
  return 0;
}
