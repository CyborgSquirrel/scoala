(DEFUN cauta-nenul (L)
       (COND
        ((NULL L) NIL)
        ((NOT (NULL (CAR L))) (CAR L))
        (T (cauta-nenul (CDR L)))))

(DEFUN cale (E L)
       (COND
        ((AND
          (LISTP L)
          (EQ (CAR L) E))
         (CONS E NIL))
        ((LISTP L)
         ((LAMBDA (Q)
                  (COND
                   ((NOT (NULL Q))
                    (CONS (CAR L) Q))
                   (T NIL)))
          (cauta-nenul
           (MAPCAR
            #'(LAMBDA (LL)
                      (cale E LL))
            L))))
        (T NIL)))
