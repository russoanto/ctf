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
Allora 
