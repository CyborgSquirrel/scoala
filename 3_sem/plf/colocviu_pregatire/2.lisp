(DEFUN f (L E1 E2)
       (COND
        ((LISTP L)
         (MAPCAR
          #'(LAMBDA (LL)
                    (f LL E1 E2))
          L))
        ((EQ L E1) E2)
        (T L)))
