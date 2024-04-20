# Fluff
## Come procede
Allora come indicato anche sul sito ho bisogno di una sorta di **mov** per inserire la stringa "flag.txt" in memoria per poi passarla alla funzione print_file. Questa mov non c'è, quindi dobbiamo capire attentamente i gadget che abbiamo a disposizione che sono:
### xlat   BYTE PTR ds:[rbx]
Allora da quello che ho capito con questo gadget possiamo andare a scrivere nel registro **AL**, il dato da inserire in AL viene recuperato dall'indirizzo base in ds + un offset specificato in RBX. Quindi con questo gadget possiamo andare a scrivere nel registro AL se abbiamo le seguenti dipendenze:
- [] ds: dobbiamo poter scrivere in ds
- [x] RBX: dobbiamo poter scrivere in rbx

### bextr  rbx,rcx,rdx
Bit field extract ci permette di estrarre dei bit, ma in che modo? Allora prima cosa sappiamo che il registro di **destinazione** in cui i bit verranno inseriti è **rbx** (ora soddisfiamo la dipendenza sopra citata). **rcx** è il registro da dove verrano prelevati i bit, ed in fine **rdx** è il registro che contiene la maschera di estrazione dei bit (devo ancora ben capire come utilizzarlo). Le dipendenze che presenza questo gadget sono:
- [x] rcx: ho la pop
- [x] rdx: ho la pop

### stos   BYTE PTR es:[rdi],al
Questo è il gadget che mi permette di scrivere il contenuto del registro AL in una zono di memoria che voglo, quindi proprio quello che voglio, l'indirizzo di destinazione viene calcolato sommando l'indirizzo contenuto nel registro **es** più il contenuto del registro **rdi**. Come dipendenze abbiamo:
- [] es: come scrivo su es ??
- [x] rdi: ho la pop

### Mie considerazioni
Ho trovato qualcosa di interessante sui registri segment di cui fanno parte ds ed es:
Segment registers

Segment registers hold the segment address of various items. They are only available in 16 values. They can only be set by a general register or special instructions. Some of them are critical for the good execution of the program and you might want to consider playing with them when you'll be ready for multi-segment programming

CS         : Holds the Code segment in which your program runs.
             Changing its value might make the computer hang.

DS         : Holds the Data segment that your program accesses.
             Changing its value might give erronous data.

ES,FS,GS   : These are extra segment registers available for
             far pointer addressing like video memory and such.

SS         : Holds the Stack segment your program uses.
             Sometimes has the same value as DS.
             Changing its value can give unpredictable results,
             mostly data related.

#### DS
Usando GDB noto che il registro datasegment è vuoto quindi potenzialmente mi basta imostare un offset che in realtà è il registro di dove voglio scrivere.

#### Starting address 
Per individuare l'indirizzo iniziale di un binario da gdb posso dare il comando
`info proc mappings`

#### Punto chiave
Leggendo la documentazione di xlat ho avuto l'illuminazione, non posso io inserire flag.txt perchè xlat richiede di inserire nel registro al il valore contenuto in un altra area di memoria. Ma se io riesco ad inseire flag.txt in un area di memoria allora non ho bisogno di passare per il regitro AL. Il punto in questa sfida è che io non ho nessun modo per inserire queta sitringa in memoria così com'è, quello che devo fare è individuare nel file i caratteri che compongono la parola 'flag.txt' ed uno per uno li inserisco nel registro AL. Da qui il gioco è fatto (spero) 
