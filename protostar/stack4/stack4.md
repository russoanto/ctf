## Stack 4
Stack4 takes a look at overwriting saved EIP and standard buffer overflows.
This level is at /opt/protostar/bin/stack4
## Code 
```c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void win()
{
  printf("code flow successfully changed\n");
}

int main(int argc, char **argv)
{
  char buffer[64];

  gets(buffer);
}
``` 
### Solution
Con gdb vado a recuperare l'indirizzo della funzione win che è il seguente: **0x80483fa**



