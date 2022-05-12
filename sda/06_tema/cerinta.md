TAD Multidicționar

Creați un iterator peste valorile asociate unei chei.

// creeaza un iterator peste valorile asociate cheii k. În cazul în care k nu este în multidicționar, iteratorul va fi nevalid imediate dupa creare. În caz contrar, elementul curent este prima valoare asociată cheii.

IteratorValori iterator(TCheie k);

Se va crea clasa IteratorValori cu aceleași operații ca și ale IteratorMultidictionar, cu excepția faptului că constructorul primește ca parametru multidicționarul și cheia și funcționează diferit, în sensul că element returnează o valoare de tipul TValoare. 
