# ret2win
Prima cosa installo pwntools ed uso le funzioni:
 - pwn template: con cui mi creo un piccolo exploit con cui posso interagire con l'eseguibile
 - pwn checksec binario: vedo tutte le caratteristiche del binario vedendo eventuali misure di sicurezza adoperate

## GDB
Passando all'opera prima di utilizzare ghidra ho deciso di fare un analisi preliminare con gdb. Listando le varie funzioni quello che trovo sono le seguenti:
 - 0x0000000000400690  frame_dummy
 - 0x0000000000400697  main
 - 0x00000000004006e8  pwnme
 - 0x0000000000400756  ret2win
 
 Main semplicemente chiama pwnme, pwnme da un primo sguardo alloca un buffer di 32 byte e questo lo sappiamo perchè come primo parametro della funzione inseriamo il valore 0x20 (32 in decimale)
  
  '
   0x00000000004006ec <+4>:     sub    rsp,0x20
   0x00000000004006f0 <+8>:     lea    rax,[rbp-0x20]
   0x00000000004006f4 <+12>:    mov    edx,0x20
   0x00000000004006f9 <+17>:    mov    esi,0x0
   0x00000000004006fe <+22>:    mov    rdi,rax
   0x0000000000400701 <+25>:    call   0x400580 <memset@plt>
  '
A questo punto vediamo che ci basta chiamare la funzione ret2win per vincere, quindi l'idea è quella di piazzare come indirizzo di ritorno da pwnme non il main ma ret2win.
