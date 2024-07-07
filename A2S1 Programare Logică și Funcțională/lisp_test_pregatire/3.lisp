(DEFUN tema-any (lista)
       (COND
        ((NULL lista) NIL)
        ((CAR lista) T)
        (T (tema-any (CDR lista)))))

; 1. Sa se construiasca o functie care
; intoarce adancimea unei liste.

(DEFUN tema-1 (lista)
       (COND
        ((LISTP lista)
         (+ 1 (APPLY 'MAX (MAPCAR #'tema-1 lista))))
        (T 0)))

; 2. Definiti o functie care obtine
; dintr-o lista data lista tuturor
; atomilor care apar, pe orice nivel,
; dar in aceeasi ordine.
;
; De exemplu
; (((A B) C) (D E)) --> (A B C D E)

(DEFUN tema-2 (element)
       (COND
        ((LISTP element)
         (APPLY #'APPEND
                (MAPCAR #'tema-2 element)))
        (T (CONS element NIL))))

; 3. Sa se construiasca o functie care
; verifica daca un atom e membru al
; unei liste nu neaparat liniara.

(DEFUN tema-3 (element lista)
       (COND
        ((LISTP lista)
         (tema-any
          (MAPCAR
           #'(LAMBDA
              (lista-lambda)
              (tema-3 element lista-lambda))
           lista)))
        (T (EQ element lista))))

; 4. Sa se construiasca o functie
; care intoarce suma atomilor numerici
; dintr-o lista, de la orice nivel.

(DEFUN tema-4 (lista)
       (COND
        ((LISTP lista) (APPLY '+ (MAPCAR #'tema-4 lista)))
        ((NUMBERP lista) lista)
        (T 0)))

; 5. Definiti o functie care testeaza
; apartenenta unui nod intr-un arbore
; n-ar reprezentat sub forma (radacina
; lista_noduri_subarb1... lista_noduri_
; _subarbn)
; Ex: arborelele este ; (a (b (c)) (d) (e (f)))
; si nodul este 'b => adevarat

; 6. Sa se construiasca o functie care
; intoarce produsul atomilor numerici
; dintr-o lista, de la orice nivel.

(DEFUN tema-6 (lista)
       (COND
        ((LISTP lista) (APPLY '* (MAPCAR #'tema-6 lista)))
        ((NUMBERP lista) lista)
        (T 1)))

; 7. Sa se scrie o functie care
; calculeaza suma numerelor pare
; minus suma numerelor impare la toate
; nivelurile unei liste.

(DEFUN tema-7 (lista)
       (COND
        ((LISTP lista) (APPLY '+ (MAPCAR #'tema-7 lista)))
        ((NUMBERP lista)
         (COND
          ((EQ 0 (MOD lista 2)) lista)
          (T (- 0 lista))))
        (T 0)))

; 8. Sa se construiasca o functie care
; intoarce maximul atomilor numerici
; dintr-o lista, de la orice nivel.

; 9. Definiti o functie care substituie
; un element E prin elementele unei
; liste L1 la toate nivelurile unei
; liste date L.

; 10. Definiti o functie care determina
; numarul nodurilor de pe nivelul k
; dintr-un arbore n-ar reprezentat sub
; forma (radacina lista_noduri_subarb1
; ... lista_noduri_subarbn)
; Ex: arborelele este
; (a (b (c)) (d) (e (f))) si k=1 =>
; 3 noduri

; 11. Sa se scrie o functie care sterge
; toate aparitiile unui atom de la
; toate nivelurile unei liste.

; 12. Definiti o functie
; care inlocuieste un nod cu
; altul intr-un arbore n-ar
; reprezentat sub forma (radacina
; lista_noduri_subarb1...lista_noduri_subarbn)
; Ex: arborelele este
; (a (b (c)) (d) (e (f))) si nodul
; 'b se inlocuieste cu nodul 'g =>
; arborele (a (g (c)) (d) (e (f)))

; 13. Definiti o functie care
; substituie un element prin altul la
; toate nivelurile unei liste date.

; 14. Definiti o functie care
; da adancimea unui arbore n-ar
; reprezentat sub forma (radacina
; lista_noduri_subarb1...lista_noduri_subarbn)
; Ex: adancimea arborelui este
; (a (b (c)) (d) (e (f))) este 3

; 15. Sa se construiasca o functie care
; intoarce numarul atomilor dintr-o
; lista, de la orice nivel.
