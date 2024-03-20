
## Level 07
The flag07 user was writing their very first perl program that allowed them to ping hosts to see if they were reachable from the web server.

To do this level, log in as the level07 account with the password level07. Files for this level can be found in /home/flag07.

## Code
```
#!/usr/bin/perl

use CGI qw{param}; # guardare cos'è il protocollo cgi

print "Content-type: text/html\n\n";

sub ping {
  $host = $_[0];

  print("<html><head><title>Ping results</title></head><body><pre>");

  @output = `ping -c 3 $host 2>&1`; #Cambio il canale di standar error con quello di standard out
 
  foreach $line (@output) { print "$line"; }

  print("</pre></body></html>");
  
}

# check if Host set. if not, display normal page, etc

ping(param("Host"));
```
### Solution
Come prima cosa concentriamoci sul codice sopra mostrato, alla riga 16 vediamo come il comando '$host = $_[0]' assegna alla variabile host il primo argomento passato alla subroutine. Successivamente viene stampato uno scheletro di pagina html. La riga fatidica è la 20 il cui viene fatto '@output = `ping -c 3 $host 2>&1`;' senza controllare l'input in ingresso. E dopo tutte le stringhe nella variabile @output vengono stampate.
#### Patter malevolo
Un pattern malevolo per l'ignezione di comandi che ci è stato mostrato è il seguente:
```
INPUT  = INPUT LEGITTIMO + CARATTERE SEPARATORE + COMANDO ARBITRARIO + CARATTERE CHIUSURA
```
Sapendo ciò un primo abbozzo di attacco potrebbe essere il seguente:
```
$host = "127.0.0.1" + ";" + "getflag" + "#"
```
Con la gratella vado a commentare tutto ciò che viene dopo che è roba su cui io non ho controllo.

#### CGI Perl - Come funziona ?
Per forza di cose bisogna interagire con un webserver, e quello che notiamo con un analisi statica del sistema è il file '/home/flag07/thttpd.conf' che ha tutta l'aria di essere un file di configurazione del webserver. Per maggiori approfondimenti su [thttpd](https://en.wikipedia.org/wiki/Thttpd). Andando a fare un grep su port quello che appare è che abbiamo unwebserver sulla porta 7007. Per controllare meglio veroificare le porte aperte sulla macchina con il comando 'ss -ntl' in questo modo posso vedere i socket TCP in ascolto sulla macchina

