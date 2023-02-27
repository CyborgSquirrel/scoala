; Pentru urmatoarele probleme se cer functii Lisp care
; folosesc functii MAP:

; 5. Definiti o functie care testeaza apartenenta unui
; nod intr-un arbore n-ar reprezentat sub forma (radacina
; lista_noduri_subarb1...lista_noduri__subarbn)

; Ex: arborelele este (a (b (c)) (d) (e (f))) si nodul este
; 'b => adevarat

; tema-list-or(elements)
; elements - lista asupra elementelor careia va fi aplicata operatia 'sau'

(DEFUN tema-list-or (elements)
       (COND
        ((NULL elements) NIL)
        ((CAR elements) T)
        (T (tema-list-or (CDR elements)))))

; tema-tree-contains(element, tree)
; element - elementul pentru care se testeaza apartenenta la arbore
; tree - arborele in care se cauta elementul

(DEFUN tema-tree-contains (element tree)
       (COND
        ((NULL tree) NIL)
        ((EQ (CAR tree) element) T)
        (T
         (tema-list-or
          (MAPCAR
           #'(LAMBDA
              (tree-lambda)
              (tema-tree-contains element tree-lambda))
           (CDR tree))))))

(ASSERT (tema-tree-contains 'b '(a (b (c)) (d) (e (f)))))
(ASSERT (tema-tree-contains 'f '(a (b (c)) (d) (e (f)))))
(ASSERT (tema-tree-contains 'a '(a (b (c)) (d) (e (f)))))
(ASSERT (NOT (tema-tree-contains 'xyz '(a (b (c)) (d) (e (f))))))
(ASSERT (NOT (tema-tree-contains 1 '(a (b (c)) (d) (e (f))))))

(ASSERT (tema-tree-contains 'g '(a (b (c) (d (e)) (f (g) (h)) (i (j (k (l))))))))
(ASSERT (tema-tree-contains 'l '(a (b (c) (d (e)) (f (g) (h)) (i (j (k (l))))))))
(ASSERT (NOT (tema-tree-contains 'x '(a (b (c) (d (e)) (f (g) (h)) (i (j (k (l)))))))))
