Teoria automatelor finite extinsă cu:
- o notație pentru imbricarea unei mașini de stări într-alta, sub formă de stare
- o notație ce permite etichetarea tranzițiilor cu mesaje trimise și condiții impuse asupra obiectelor

Stare: Condiție satisfăcută de valorile unui obiect.

Tranziție: Schimbare de stare, care poate fi provocată de îndeplinierea unor condiții.

![[Pasted image 20230604184032.png]]

![[Pasted image 20230604184201.png]]

Acțiune: Funcție atomică care poate primi input-uri, poate produce output-uri, și poate schimba starea sistemului.

Acțiunea poate fi declanșată de:
- ieșirea dintr-o stare
- o tranziție
- intrarea într-o stare

Acțiunile se execută în funcție de ceea ce le declanșează, în aceeași ordine ca mai sus.

Tranziție internă: Tranziție prin care nu se părăsește starea curentă. Nu se execută acțiunile de intrare / ieșire.

Activitate: Mulțime coordonată de acțiuni. Durează mai mult timp, pot fi întrerupte la ieșirea obiectului din starea curentă.

![[Pasted image 20230604185329.png]]

Submașină de stări.

![[Pasted image 20230604185448.png]]