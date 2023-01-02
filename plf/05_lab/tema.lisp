; 7.

; a) Sa se scrie o functie care testeaza daca o lista
;    este liniara.

; tema-is-linear(L: List)
; L - lista pentru care se va verifica daca este liniara

(DEFUN tema-is-linear(L)
       (COND
        ((NULL L) T)
        ((NOT (ATOM (CAR L))) NIL)
        (T (tema-is-linear (CDR L)))))

(assert (tema-is-linear '(6 3 12)))
(assert (tema-is-linear '(1 nil 2 4 10 13 43 x y z)))
(assert (not (tema-is-linear '(1 nil (5 6 (1 5)) 4 (1 2) 13 43 x y z))))

; b) Definiti o functie care substituie prima aparitie a
;    unui element intr-o lista data.

; tema-subsitute(E: Atom, NE: Atom, L: List)
; E - elementul care va fi substituit
; NE - valoarea noua a elementului
; L - lista in care se va efectua substitutia

(DEFUN tema-subsitute(E NE L)
       (COND
        ((EQUAL (CAR L) E) (CONS NE (CDR L)))
        ((NOT (NULL L)) (CONS (CAR L) (tema-subsitute E NE (CDR L))))
        (T NIL)))

(assert (equal (tema-subsitute 'x 'z '(a b x 12 e)) '(a b z 12 e)))
(assert (equal (tema-subsitute 'x 'z '(1 2 3))      '(1 2 3)))

; c) Sa se inlocuiasca fiecare sublista a unei liste cu
;    ultimul ei element. Prin sublista se intelege element
;    de pe primul nivel, care este lista.
; Exemplu:
;     (a (b c) (d (e (f))))
; ==> (a c (e (f)))
; ==> (a c (f))
; ==> (a c f)
; Exemplu:
;     (a (b c) (d ((e) f)))
; ==> (a c ((e) f))
; ==> (a c f)

; tema-last-element(L: List)
; L - lista in care se cauta ultimul element de pe ultimul nivel

(DEFUN tema-last-element(L)
       (COND
        ((ATOM L) L)
        ((NULL (CDR L)) (tema-last-element (CAR L)))
        (T (tema-last-element (CDR L)))))

; tema-last-element-substitute(L: List)
; L - lista in care se va inlocui fiecare lista cu ultimul element de pe ultimul nivel al sau

(DEFUN tema-last-element-substitute(L)
       (COND
        ((NULL L) NIL)
        (T (CONS
            (tema-last-element (CAR L))
            (tema-last-element-substitute (CDR L))))))

(assert (equal (tema-last-element-substitute '(a (b c) (d (e (f))))) '(a c f)))
(assert (equal (tema-last-element-substitute '(a (b c) (d ((e) f)))) '(a c f)))

; d) Definiti o functie care interclaseaza fara pastrarea
;    dublurilor doua liste liniare sortate.

; tema-merge(L1: List, L2: List)
; L1 - prima lista care va fi interclasata
; L2 - a doua lista care va fi interclasata

(DEFUN tema-merge(L1 L2)
       (COND
        ((AND (NULL L1) (NULL L2)) NIL)
        ((NULL L2) L1)
        ((NULL L1) L2)
        ((EQUAL (CAR L1) (CADR L1))
         (tema-merge (CDR L1) L2))
        ((EQUAL (CAR L2) (CADR L2))
         (tema-merge L1 (CDR L2)))
        ((EQUAL (CAR L1) (CAR L2))
         (CONS (CAR L1) (tema-merge (CDR L1) (CDR L2))))
        ((< (CAR L1) (CAR L2))
         (CONS (CAR L1) (tema-merge (CDR L1) L2)))
        ((> (CAR L1) (CAR L2))
         (CONS (CAR L2) (tema-merge L1 (CDR L2))))))

(assert (equal (tema-merge
                '(18 63 87)
                '(16 32 34 37 82 88 94))
               '(16 18 32 34 37 63 82 87 88 94)))

(assert (equal (tema-merge
                '(18 63 63 63 63 87)
                '(16 32 34 34 34 34 34 37 63 63 82 88 88 94))
               '(16 18 32 34 37 63 82 87 88 94)))
