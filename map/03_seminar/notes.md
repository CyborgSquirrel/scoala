### serializare (Serializable)

este o interfata pentru a serializa / deserializa obiecte

trebuie sa fie implementate `writeObject()`, `readObject()`, `readObjectNoData()`

### serialVersionUID

Numarul versiunii de serializare a claselor.
 
### getResource

Returneaza un url la un fisier, relativ la locatia clasei pe care am apelat metoda.

### FileReader

Clasa pentru citirea a sirurilor de caractere din fisiere.

### readAllLines(path, charset)

Citeste toate liniile de text din fisierul aflat la `path`, si le returneaza sub forma de lista de stringuri.
 
### ObjectOutputStream

Scrie tipuri de date primitive si obiecte intr-un stream. Obiectele trebuie sa fie `Serializable`.

### writeObject

Metoda a `ObjectOutputStream` care scrie un obiect in stream.
