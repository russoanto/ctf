#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *file;
  char *host;

  if(argc < 3) {
      printf("%s file host\n\tsends file to host if you have access to it\n", argv[0]);
      exit(1);
  }
  
  file = argv[1]; // stringa del file che voglio inviare
  host = argv[2]; // host a cui voglio inviare il file
  
  // cos'è access? vado su man, controllo se il processo invocante può accedere al file
  if(access(argv[1], R_OK) == 0) {
      int fd;
      int ffd;
      int rc;
      struct sockaddr_in sin; // api socket [riguardare un minimo] 
      char buffer[4096];

      printf("Connecting to %s:18211 .. ", host); // funzione lentissima
      fflush(stdout); // tutto ciò che non ho ancora scritto su terminale lo vado a scriver
      // tutto ciò va a ralentare 

      fd = socket(AF_INET, SOCK_STREAM, 0); // definisco un socket

      memset(&sin, 0, sizeof(struct sockaddr_in)); //pulisco la struttura dati e la riempio di 0
      sin.sin_family = AF_INET;
      sin.sin_addr.s_addr = inet_addr(host);
      sin.sin_port = htons(18211); //porta a cui voglio connettermi
      // Pacchetti ethernet [può tornare utile]

      if(connect(fd, (void *)&sin, sizeof(struct sockaddr_in)) == -1) { // mi connetto via tcp
          printf("Unable to connect to host %s\n", host);
          exit(EXIT_FAILURE);
      }

#define HITHERE ".oO Oo.\n"
      if(write(fd, HITHERE, strlen(HITHERE)) == -1) { // scrivo su socket HITHERE 
          printf("Unable to write banner to host %s\n", host);
          exit(EXIT_FAILURE);
      }
#undef HITHERE
    // è passato molto tempo da quando ho controllato se il file è scrivibile, teniamolo a mente
      printf("Connected!\nSending file .. "); fflush(stdout);

      ffd = open(file, O_RDONLY); // finalmente apro il file
      if(ffd == -1) {
          printf("Damn. Unable to open file\n");
          exit(EXIT_FAILURE);
      }

      rc = read(ffd, buffer, sizeof(buffer)); //leggo il token
      if(rc == -1) {
          printf("Unable to read from file: %s\n", strerror(errno));
          exit(EXIT_FAILURE);
      }

      write(fd, buffer, rc); // se riesco a leggerlo lo mando sul soket

      printf("wrote file!\n");

  } else {
      printf("You don't have access to %s\n", file);
  }
}
