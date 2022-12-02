; 7.

; a) Sa se scrie o functie care testeaza daca o lista
;    este liniara.

(DEFUN tema-is-linear(L)
       (COND
        ((NULL L) T)
        ((NOT (ATOM (CAR L))) NIL)
        (T (tema-is-linear (CDR L)))))

; b) Definiti o functie care substituie prima aparitie a
;    unui element intr-o lista data.

(DEFUN tema-subsitute(E NE L)
       (COND
        ((EQUAL (CAR L) E) (CONS NE (CDR L)))
        ((NOT (NULL L)) (CONS (CAR L) (tema-subsitute E NE (CDR L))))
        (T NIL)))

; c) Sa se inlocuiasca fiecare sublista a unei liste cu
;    ultimul ei element. Prin sublista se intelege element
;    de pe primul nivel, care este lista.
; Exemplu:
;     (a (b c) (d (e (f))))
; ==> (a c (e (f)))
; ==> (a c (f))
; ==> (a c f)
;     (a (b c) (d ((e) f)))
; ==> (a c ((e) f))
; ==> (a c f)

(DEFUN tema-last-element(L)
       (COND
        ((ATOM L) L)
        ((NULL (CDR L)) (CAR L))
        (T (tema-last-element (CDR L)))))

(DEFUN tema-last-element-substitute(L)
       (COND
        ((NULL L) NIL)
        (T (CONS
            (tema-last-element (CAR L))
            (tema-last-element-substitute (CDR L))))))

; d) Definiti o functie care interclaseaza fara pastrarea
;    dublurilor doua liste liniare sortate.

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
