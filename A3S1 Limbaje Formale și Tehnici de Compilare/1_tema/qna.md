# Intrebari intrebatoare

_Q:_ La tip de date definit de utilizator, cerinta este sa facem ca
mini-limbajul sa suporte creearea unor tipuri de date noi (adica sa poti defini
`struct Elefant { nume: String, greutate: f32 }`)? Sau sa adaugam noi pur si
simplu un tip de date in plus?

_A:_ Trebuie sa poti defini struct nou in mini limbaj.

_Q_: Trebuie sa punem in gramatica chestia cu "identificatori de lungime
oarecare nedepasind 250 caractere"?

_A:_ Da.

_Q_: Ce trebuie sa faca mai exact analizorul lexical? Trebuie pur si
simplu sa scoata toti atomii? Sau trebuie sa verifice daca structura programului
este conform EBNF-ului?

_A:_ First one. Trebuie doar sa scoata atomii.

_Q:_ Exista un mod sa excludem un caracter in EBNF? de exemplu intre
ghilimele sa poate aparea orice caracter, in afara de o alta ghilimea.

_A:_
