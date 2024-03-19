# Level 05
## Topic
Permessi di accesso generosi ad un archivio contenente chiavi SSH
## Solution
Inizialmente faccio un:
`find /home/ -readable 2>/dev/null`
e l'output che ottengo è situato nel file out.txt, e quello che possiamo notare è il file 
/home/flag05/.backup/backup-19072011.tgz, sembra proprio essere un backup e può contenere qualcosa di utile. Quello che noto è che ho l'opportunità di leggerlo, quindi quello che faccio è fare scp sul host locale.
### Perchè ho fatto scp?
lanciando il `tar -tf pathBackup` quello che vedo è che ho le chiavi pubbliche e private di flag05, l'idea è di scaricarle e usarle per loggarmi.
### Come uso la chiave privata??
Una volta presa la chiave privata, posso usare il parametro di ssh `PubkeyAcceptedKeyTypes=+ssh-rsa`, che mi permette di specificare la chiave privata con cui fare il login, quindi il comando finale sarà:
    - `ssh -o PubkeyAcceptedKeyTypes=+ssh-rsa -i <chiavePrivata> flag05@ip`
Nello specifico l'opzione `-o` di ssh mi permette di specificare un opzione. Loggati come utente flag05.

