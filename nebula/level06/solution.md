# Level06
## Topic
Permessi di accesso generosi ad una password “legacy”
## Soluzione
Allora questa è un pò più terra terra, quello che faccimao all'inizio è andare a cercare cosa possiamo o non possiamo leggere, e quello che salta fuori è che leggendo il file `/etc/passwd` possiamo notare che per l'utente flag06 è contenuto l'hash della password e non una x come avviene nei sistemi moderni.
`cat /etc/passwd | grep flag06` --> `flag06:ueqwOCnSGdsuM:993:993::/home/flag06:/bin/sh`
### Che hash è???
Cosa me ne faccio dell'hash? prima cosa devo capire che tipo di hash si tratta e per farlo posso usare il comando `hashid` (non presente di default in arch). Usando hashid l'output che ottendo è il seguente:
`   Analyzing 'ueqwOCnSGds
    [+] Des(Unix)
    [+] Traditional DES 
    [+] DEScrypt ` 
!!Ottimo, des fa schifo, ora si cracca. Uno dei software di hash crack più famosi è hashcat. Allora per hashcat, se non hai la scheda video integrata bisogna scaricare le API di CUDA altrimenti non va una fava. Il comando utilizzato è il seguente `hashcat -a 0 -m 1500 flag06.txt <dizionario>`.
    - -a 0 : indica il tipo di attacco, nel nostro caso a dizionario
    - -m 1500: indica il tipo di funzione hash, nel nostro caso DES
    - l'output di hashcat si trova in un file .potfile contenuto nella cartella `/home/arusso/.local/share/hashcat/hashcat.potfile`

