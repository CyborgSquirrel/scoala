- Pot două procese să ocupe același port?
- NU

`socket()` returnează un descriptor de socket
```c
sockfd = socket(AF_INET, TCP, IPV4);
```

`(tip_structură, ip_server, port_server)` este o structură
```c
int code = connect(
	s, (AF_INET, ip_server, port_server), sizeof(structură)
);
if (code < 0) {
	// eroare
}
```

Dacă totul este ok, facem:
```c
send(sockfd, buf, len, 0);
recv(sockfd, buf, len, flags);
```

Procesul server:
```c
// addr = INADDR_ANY = 0.0.0.0
int code = bind(sockfd, addr, addrlen);
if (code < 0) {
	// eroare
}
```

Este posibil ca două procese sa asculte pe același port, dacă proprietățile socket-urilor sunt diferite (ip-uri diferite, protocoale diferite).

Adresă IPv4:
- 4 octeți

Adresă IPv6:
- 16 octeți

- `inet_addr(string)` convertește un string într-o structură de adresă
- `inet_ntoa(addr)` (network to ascii) convertește o adresă într-un string

Pachet:
- ip server
- port server
- ip client
- port client

### Server iterativ

Servește clienții pe rând.

```c
// backlog = 5
listen(sockfd, backlog);
while (1) {
	int clientfd = accept(
		  sockfd
		, out_client_addr
		, out_client_addrlen
	);
	recv(clientfd, ...);
	send(clientfd, ...);
	close(clientfd);
}
close(sockfd);
```

### Server concurent

Servește clienții în paralel.

```c
// backlog = 5
listen(sockfd, backlog);
while (1) {
	int clientfd = accept(
		  sockfd
		, out_client_addr
		, out_client_addrlen
	);
	pid_t pid = fork();
	if (fork == 0) {
		recv(clientfd, ...);
		send(clientfd, ...);
		close(clientfd);
		exit(0);
	}
}
close(sockfd);
```

### Funcții de conversie a ordinii octeților

- `htons()` host to network short
- `ntohs()` network to host short
- `htonl()` host to network long
- `ntohl()` network to host long
- ...
