Dimensiunea maximă a unui pachet IP: 64KB.

MTU = Maximum Transfer Unit

Este posibil ca un server să servească pe aceeași combinație de (ip, port) și TCP și UDP.

## Socket-uri UDP

### Client

```c
c = socket(AF_INET);
// nu e nevoie de connect()
sendto(c, buf, buf_len, flags, dest, dest_len);
recvfrom(c, buf, buf_len, flags, src, src_len);
close(c);
```

### Server

```c
s = socket(AF_INET, SOCK_DGRAM);
bind(s, ...);
// nu e nevoie de listen()
// nu e nevoie de accept()
while (1) {
	recvfrom(c, buf, buf_len, flags, src, src_len);
	
	// faci fork()
	// fiul face socket() si bind() pe un port nou
	// si trimite raspunsul prin acel socket
	
	// sendto trimite datele unui partener, ale cărui date de identificare (ip, port) sunt completate de recvfrom
	sendto(c, buf2, buf2_len, flags, src, src_len);
}
```

## Structură pachet TCP

- header
	- port sursă
	- port destinație
	- număr de secvență (număr de octeți transmiși kinda)
	- număr de confirmare
	- flaguri
		- `SYN`
		- `ACK`
		- `FIN`
		- ...
	- checksum
	- ...
- date

### 3-way handshake

- `SYN`
- `SYN`,`ACK`
- `ACK`

### close()

Se trimite un pachet cu flag-ul `FIN`.

## Structură pachet UDP

- header
	- port sursă
	- port destinație
	- lungime
	- checksum
- date

## Structură pachet IP

- header
	- versiune
	- lungimea pachetului
	- header checksum
	- TTL (Time To Live)
	- IP sursă
	- IP destinație
	- ...
- pachet TCP/UDP
