# Stack 05
## Stack based overflow

int main(int argc, char **argv)
{
	char buffer[64];
	gets(buffer);
}

## Cosa fa gets? 
Prima di tutto guardiamo la documentazione (man gets), quello che scopriamo è che gets non fa nessun controllo sulla lunghezza del buffer. Quindi possiamo inondare il buffer senza controlli. Possiamo oltretutto notare che nella pagina di manuale c'è chiaramente scritto nella sezione *bugs* che non deve essere usato e al suo posto va utilizzato *fgets()*. Quello che cambia è che chiede come secondo parametro il numero di bytes da leggere, quindi non possiamo inondare il buffer.
## Cosa succede se diamo più di 64 bytes?
Esiste qualche comando che ci permette di analizzare il memory layout di linux? Quello che scopiramo è che esiste pmap. Quello che posso fare è vedere come sono distribuite le aree di memoria di un processo e tra le varie aree c'è lo stack che è in modalità di lettura, scrittura ed eseguibile. UN area di memoria MAI deve essere ESEGUIBILE. Esistono delle pagine definite di guardia con permessi nulli (-----) che servo ad evitare che la memoria venga inondata di dati a caso, questo perchè quando incontrano la pagina di guardia c'è un errore visto che si sta accedendo ad un area di memoria senza permessi.

## Analizzo il binario
Usando gdb quello che posso fare è analizzare le prime 10 istruzioni
`gdb ./stack5` e successivamente `x/10i main` (stampo le prime 10 istruzioni a partire dalla funzione main). Quello che ci può tornare utile è prendere l'indirizzo della funzione main e fare l'and con -16 per ottenere il valore più grande, minore o uguale all'indirizzo del main, multiplo di 16. [Approfondimenti] Hackers Delight. Ma perchè dobbiamo fare sta roba? Lo standard dell'architettura intel siano allineate a multipli di 16 byte. In alcuni sistemi operativi se non fai questo chrasha. Quando io in assemply chiamo una funzione, i suoi argomenti li passo sullo stack, ma quindi devo fare spazio nello stack.

## Cosa mi serve?
Come faccio a generare uno zero senza usare uno zero?? `mov 0, %eax` Non posso usare direttamente 0, mov 0 comporta l'uso di una costante che è lenta e va caricata in memroia. Posso usare lo xor `xor %eax,%eax` così genero uno zero senza usare uno zero. successivamente lo pusho sullo stack `push %eax`. A questo punto posso iniziare a pushare sullo stack (al contrario perchè è little endian) e lo faccio in questo modo `push $0x68732f2f`(//sh). L'ultima cosa che manca è /bin e lo faccio così `push $0x6e69622f`. Il secondo e terzo argomento sono NULL quindi copio in %ebx e %edx il valore di %eax che contiene 0. Devo chiamare exeve, devo andare nei sorgenti del kernel (gli indici sono memroizzati in /path/to/linux/arch/x86/entry/syscalls/syscall_32.tbl). Devo mettere l'indice in `mov $0xb,%al`. Usiamo al che è la versione a 8 bit di %eax. Una volta scritto tutto il codice assembly dobbiamo compilarlo con -o per ottenere il codice macchina e disassemblando con objdump ottengo la sequenza di byte che rappresenta il mio shellcode. 
