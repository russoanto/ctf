# Bizness
## info
ip: 10.10.11.252
topic: linux
diff: easy

## Let's start
- `nmap -p 1-8000 ip`
### Results
#### Open port
- 22 ssh
- 80 http
- 443 https
### Host problem
Per raggiungere l'host devo aggiungere in /etc/hosts '10.10.11.152 bizness.htb'
### gobuster
/control

### Burpsuite
cookie: JSESSIONID=CEBCC4CD9F874E84CC0890CE5173C715.jvm1
