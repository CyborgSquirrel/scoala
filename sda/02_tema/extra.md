TAD Mulțime 

Transformați iteratorul pentru a putea elimina elementul curent. Adăugați operația următoare în clasa IteratorMultime: 

// elimină și returnează elementul curent referit de iterator 

//după efectuarea operației, elementul curent referit de iterator este următorul element din mulțime, sau, în cazul în care elementul eliminat a fost ultimul, iterator devine nevalid 

// aruncă excepție în cazul în care iteratorul este nevalid 

TElem elimina (); 

Obs: Pentru ca această operație să funcționeze, trebuie să efectuați câteva alte modificări ale codului: 
- operația iterator din Mulțime nu mai este const 
- Referința la mulțime în iterator nu mai este const (dar este încă o referință)
- Parametrul transmis constructorului clasei care implementează iteratorul nu mai este const

