# Stack 1
## Code
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  volatile int modified;
  char buffer[64];

  if(argc == 1) {
      errx(1, "please specify an argument\n");
  }

  modified = 0;
  strcpy(buffer, argv[1]);

  if(modified == 0x61626364) {
      printf("you have correctly got the variable to the right value\n");
  } else {
      printf("Try again, you got 0x%08x\n", modified);
  }
}

  ### Soluzione
Quello che succede dando in pasto tantissime lettere, e dalla stampa, fichè non si inseriscono più di 64 caratteri stamperà sempre 0x0000, altrimenti andrà a stampare le lettere in essesso. ATTENZIONE l'architettura è little endian quindi dobbiamo inserire i caratteri al contrario
