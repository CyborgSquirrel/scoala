; vale-aux (A, L)
; A - flag care poate lua 3 valori: -1 la primul
;     apel al functiei, 0 atunci cand numerele
;     sunt in ordine descendenta, si 1 atunci
;     cand numerele sunt in ordine ascendenta
; L - lista pentru care se determina daca are aspect
;     de "vale"

(DEFUN vale-aux (A L)
       (COND
        ((AND
          (NOT (NULL (CDR L)))
          (> (CAR L) (CADR L))
          (OR
           (= A -1)
           (= A 0)))
         (vale-aux 0 (CDR L)))
        ((AND
          (NOT (NULL (CDR L)))
          (< (CAR L) (CADR L))
          (OR
           (= A 0)
           (= A 1)))
         (vale-aux 1 (CDR L)))
        ((AND
          (NOT (NULL L))
          (NULL (CDR L))
          (= A 1))
         T)
        (T NIL)))

; vale (L)
; L - lista pentru care se determina daca are aspect
;     de "vale"

(DEFUN vale (L) (vale-aux -1 L))

; teste

(PRINT (vale '(1)))
(PRINT (vale '(3 1)))
(PRINT (vale '(1 2)))
(PRINT (vale '(3 1 2)))
(PRINT (vale '(3 1 3 0)))

(PRINT (vale '(10 8 6 17 19 20)))
(PRINT (vale '(10 8 6 17 19 20 0)))
(PRINT (vale '(0 10 8 6 17 19 20)))
