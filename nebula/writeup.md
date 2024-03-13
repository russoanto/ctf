ip: 192.168.1.4

# Level 01

## Source code 

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
  gid_t gid;
  uid_t uid;
  gid = getegid();
  uid = geteuid();

  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);

  system("/usr/bin/env echo and now what?");
}


# Level 02

## Source #+BEGIN_cpp 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
  char *buffer;

  gid_t gid;
  uid_t uid;

  gid = getegid();
  uid = geteuid();

  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);

  buffer = NULL;

  asprintf(&buffer, "/bin/echo %s is cool", getenv("USER"));
  printf("about to call system(\"%s\")\n", buffer);
  
  system(buffer);
}

#+END_cpp

## Problema
In questo caso abbiamo abbiamo la chiamata di sistema getenv("USER") che va a recuperare il contenuto della variabile d'ambiente USER e lo piazza nel buffer insieme alla stringa "is cool". L'idea in questo caso è modificare la variabile d'ambiente $USER e inserirci "/bin/getflag". A questo punto ci basta lanciare ./flag02 e il gioco è fatto.

# Flag 03

