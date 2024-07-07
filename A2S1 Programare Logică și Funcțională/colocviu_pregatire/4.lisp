(DEFUN ex-flatten (L)
       (COND
        ((LISTP L)
         (APPLY
          #'APPEND
          (MAPCAR
           #'ex-flatten
           L)))
        (T
         (CONS L NIL))))

(DEFUN ex-count (E L)
       (COND
        ((NULL L) 0)
        ((EQ E (CAR L))
         (+ 1 (ex-count E (CDR L))))
        (T (ex-count E (CDR L)))))

(DEFUN ex-eliminate (E L)
       (COND
        ((NULL L) NIL)
        ((EQ E (CAR L))
         (ex-eliminate E (CDR L)))
        (T
         (CONS
          (CAR L)
          (ex-eliminate E (CDR L))))))

(DEFUN ex-fin-aux (L)
       (COND
        ((NULL L) NIL)
        ((EQ
          0
          (MOD
           (ex-count (CAR L) L)
           2))
         (CONS
          (CAR L)
          (ex-fin-aux
           (ex-eliminate
            (CAR L)
            L))))
        (T
         (ex-fin-aux
          (ex-eliminate
           (CAR L)
           L)))))

(DEFUN ex-fin (L)
       (ex-fin-aux (ex-flatten L)))
