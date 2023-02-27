; 1.

; a) Sa se insereze intr-o lista liniara un atom a dat
;    dupa al 2-lea, al 4-lea, al 6-lea,....element.

(DEFUN tema-1-a-aux (A I L)
       (COND
        ((EQ I 2)
         (CONS
          A
          (tema-1-a-aux A 0 L)))
        ((NULL L) NIL)
        (T
         (CONS
          (CAR L)
          (tema-1-a-aux A (+ I 1) (CDR L))))))

(DEFUN tema-1-a (A L) (tema-1-a-aux A 0 L))

; b) Definiti o functie care obtine dintr-o lista data
;    lista tuturor atomilor care apar, pe orice nivel,
;    dar in ordine inversa.
;    De exemplu: (((A B) C) (D E)) --> (E D C B A)

(DEFUN tema-1-b)

; c) Definiti o functie care intoarce cel mai
;    mare divizor comun al numerelor dintr-o lista
;    neliniara.
; d) Sa se scrie o functie care determina numarul
;    de aparitii ale unui atom dat intr-o lista
;    neliniara.

; 2.
; a) Definiti o functie care selecteaza al n-lea
;    element al unei liste, sau NIL, daca nu exista.
; b) Sa se construiasca o functie care verifica
;    daca un atom e membru al unei liste nu neaparat
;    liniara.
; c) Sa se construiasca lista tuturor sublistelor
;    unei liste. Prin sublista se intelege fie lista
;    insasi, fie un element de pe orice nivel, care
;    este lista. Exemplu: (1 2 (3 (4 5) (6 7)) 8
;    (9 10)) => ( (1 2 (3 (4 5) (6 7)) 8 (9 10))
;    (3 (4 5) (6 7)) (45) (6 7) (9 10) ).
; d) Sa se scrie o functie care transforma o lista
;    liniara intr-o multime.

; 3.
; a) Definiti o functie care intoarce produsul a
;    doi vectori.
; b) Sa se construiasca o functie care intoarce
;    adancimea unei liste.
; c) Definiti o functie care sorteaza fara pastrarea
;    dublurilor o lista liniara.
; d) Sa se scrie o functie care intoarce intersectia
;    a doua multimi.

; 4.
; a) Definiti o functie care intoarce suma a doi
;    vectori.
; b) Definiti o functie care obtine dintr-o lista
;    data lista tuturor atomilorcare apar, pe orice
;    nivel,dar in aceeasi ordine. De exemplu:(((A B)
;    C) (D E)) --> (A B C D E)
; c) Sa se scrie o functie care plecand de la o lista
;    data ca argument, inverseaza numai secventele
;    continue de atomi. Exemplu:(a b c (d (e f)
;    g h i)) ==> (c b a (d (f e) i h g))
; d) Sa se construiasca o functie care intoarce
;    maximul atomilor numerici dintr-o lista, de la
;    nivelul superficial.

; 5.
; a) Definiti o functie care interclaseaza cu
;    pastrarea dublurilor doua liste liniare sortate.
; b) Definiti o functie care substituie un element
;    Eprin elementele unei liste L1la toate nivelurile
;    unei liste date L.
; c) Definiti o functie care determina suma a doua
;    numere in reprezentare de lista si calculeaza
;    numarul zecimal corespunzator sumei.
; d) Definiti o functie care intoarce cel mai mare
;    divizor comun al numerelordintr-o lista liniara.

; 6.
; a) Sa se scrie de doua ori elementul de pe pozitia
;    a n-a a unei liste liniare. De exemplu, pentru
;    (10 20 30 40 50) si n=3 se va produce (10 20 30
;    30 40 50).
; b) Sa se scrie o functie care realizeaza o lista
;    de asociere cu cele doualiste pe care le
;    primeste. De ex: (A B C) (X Y Z) --> ((A.X)
;    (B.Y) (C.Z)).
; c) Sa se determine numarul tuturor sublistelor
;    unei liste date, pe orice nivel. Prin sublista
;    se intelege fie lista insasi, fie un element de
;    pe orice nivel, care este lista. Exemplu: (12
;    (3 (4 5) (6 7)) 8 (9 10)) => 5 (lista insasi,
;    (3 ...), (4 5), (6 7), (9 10)).
; d) Sa se construiasca o functie care intoarce
;    numarul atomilor dintr-olista, de la nivel
;    superficial.

; 7.
; a) Sa se scrie o functie care testeaza daca o lista
;    este liniara.
; b) Definitio functie care substituie prima aparitie
;    a unui element intr-o lista data.
; c) Sa se inlocuiasca fiecare sublista a unei
;    liste cu ultimul ei element.Prin sublista
;    se intelege element de pe primul nivel, care
;    este lista. Exemplu: (a (b c) (d (e (f)))) ==>
;    (a c (e (f))) ==> (a c (f)) ==> (a c f)(a (b c)
;    (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)
; d) Definiti o functie care interclaseaza fara
;    pastrarea dublurilor doua liste liniare sortate.

; 8.
; a) Sa se elimine elementul de pe pozitia a n-a a
;    unei liste liniare.
; b) Definiti o functie care determina succesorul
;    unui numar reprezentat cifracu cifra intr-o
;    lista. De ex: (1 9 3 5 9 9) --> (1 9 3 6 0 0)
; c) Sa se construiasca multimea atomilor unei
;    liste.Exemplu: (1 (2 (1 3 (2 4) 3) 1) (1 4)) ==>
;    (1 2 3 4)
; d) Sa se scrie o functie care testeaza daca o lista
;    liniara este o multime.

; 9.
; a) Sa se scrie o functie care intoarce diferenta
;    a doua multimi.
; b) Definiti o functie care inverseaza o lista
;    impreuna cu toate sublistele sale de pe orice
;    nivel.
; c) Dandu-se o lista, sa se construiasca lista
;    primelor elemente ale tuturor elementelor lista
;    ce au un numar impar de elemente la nivel
;    superficial.Exemplu: (1 2 (3 (4 5) (6 7)) 8
;    (9 10 11)) => (1 3 9).
; d) Sa se construiasca o functie care intoarce suma
;    atomilor numerici dintr-o lista, de la nivelul
;    superficial.

; 10.
; a) Sa se construiasca o functie care intoarce
;    produsul atomilor numericidintr-o lista, de la
;    nivelul superficial.
; b) Sa se scrie o functie care, primind o lista,
;    intoarce multimea tuturor perechilor din
;    lista. De exemplu: (a b c d) --> ((a b) (a c)
;    (a d)(b c) (b d) (c d))
; c) Sa se determine rezultatul unei expresii
;    aritmetice memorate in preordinepe o
;    stiva. Exemple:(+ 1 3) ==> 4 (1 + 3)(+ * 2 4 3)
;    ==> 11 ((2 * 4) + 3)(+ * 2 4 -5 * 2 2) ==> 9
;    ((2 * 4) + (5 -(2 * 2))
; d) Definiti o functie care, dintr-o lista de atomi,
;    produce o lista de perechi (atom n), unde atom
;    apare in lista initiala de n ori. De ex:(A B A
;    B A C A) --> ((A 4) (B 2) (C 1)).

; 11.
; a) Sa se determine cel mai mic multiplu comun al
;    valorilor numerice dintr-o lista neliniara.
; b) Sa se scrie o functie care sa testeze daca o
;    lista liniara formata dinnumere intregi are
;    aspect de "munte"(o secvență se spune ca are
;    aspect de "munte" daca elementele cresc pana la
;    un moment dat, apoi descresc. De ex.10 18 29 17
;    11 10).
; c) Sa se elimine toate aparitiile elementului
;    numeric maxim dintr-o lista neliniara.
; d) Sa se construiasca o functie care intoarce
;    produsul atomilor numerici pari dintr-o lista,
;    de la orice nivel.

; 12.
; a) Definiti o functie care intoarce produsul scalar
;    a doi vectori.
; b) Sa se construiasca ofunctie care intoarce
;    maximul atomilor numerici dintr-o lista, de la
;    orice nivel.
; c) Sa se scrie o functie care intoarce lista
;    permutarilor unei liste date.
; d) Sa se scrie o functie care intoarce T daca
;    o lista are numar par de elemente pe primul
;    nivel si NIL in caz contrar, fara sa se numere
;    elementele listei.

; 13.
; a) Sa se intercaleze un element pe pozitia a n-a
;    a unei liste liniare.
; b) Sa se construiasca o functie care intoarce
;    suma atomilor numerici dintr-o lista, de la
;    orice nivel.
; c) Sa se scrie o functie care intoarce multimea
;    tuturor sublistelor unei liste date. Ex:
;    Ptr. lista ((1 2 3) ((4 5) 6)) => ((1 2 3) (4 5)
;    ((4 5) 6))
; d) Sa se scrie o functie care testeaza egalitatea a
;    doua multimi, fara sa se faca apel la diferenta
;    a doua multimi.

; 14.
; a) Dandu-se o lista liniare, se cere sa se elimine
;    elementele din Nin N.
; b) Sa se scrie o functie care sa testeze daca o
;    lista liniara formata din numere intregi are
;    aspect de "vale"(o secvență se spune ca are
;    aspect de "vale" daca elementele descresc pana
;    la un moment dat, apoi cresc. De ex. 10 8 6 17
;    19 20).
; c) Sa se construiasca o functie care intoarce
;    minimul atomilor numericidintr-o lista, de la
;    orice nivel.
; d) Sa se scrie o functie care sterge dintr-o
;    lista liniara toate aparitiile elementului
;    maxim numeric.

; 15.
; a) Sa se scrie o functie care intoarce reuniunea
;    a doua multimi.
; b) Sa se construiasca o functie care intoarce
;    produsul atomilor numerici dintr-o lista, de la
;    orice nivel.
; c) Definiti o functie care sorteaza cu pastrarea
;    dublurilor o lista liniara.
; d) Definiti o functie careconstruiește o listă
;    cu pozițiile elementului minim dintr-o listă
;    liniară numerică.
