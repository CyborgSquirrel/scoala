[[operație atomică]]

Operație atomică, care compară valoarea de la o adresă cu valoarea care se așteaptă să fie acolo, și în caz că sunt egale, atribuie acelei adrese valoarea nouă.

- se citește o valoare $A$ de la o adresă $V$
- se calculează o valoare nouă $B$
- se folosește CAS pentru a se scrie valoarea nouă; CAS compară valoarea veche $A$ cu valoarea curentă la $V$
	- dacă sunt egale:
		- se scrie $B$ în adresa $V$
	- dacă nu sunt egale:
		- instrucțiunea eșuează
		- întreg procesul poate fi repetat, până se termină cu succes