(DEFUN inl (K L)
       (COND
        ((AND (= K 0) (ATOM L)) 0)
        ((AND (> K 0) (LISTP L))
         (MAPCAR
          #'(LAMBDA
             (LL)
             (inl (- K 1) LL))
          L))
         (T L)))
