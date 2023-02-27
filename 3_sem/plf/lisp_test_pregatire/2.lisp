; Pentru urmatoarele probleme se cer functii Lisp
; programate in mod recursiv (eventual folosind
; functii MAP).
; 
; Un arbore binar se memoreaza in urmatoarele doua
; moduri:
; 
; 1. (nod nr-subarbori lista-subarbore-1
;    lista-subarbore-2 ...)
; 2. (nod (lista-subarbore-1) (lista-subarbore-2))
; 
; de exemplu arborele
; 
;   A
;  / \
; B   C
;    / \
;    D  E
; 
; se poate reprezenta astfel in cele doua moduri:
; 
; 1. (A 2 B 0 C 2 D 0 E 0)
; 2. (A (B) (C (D) (E)))
; 
; Exceptand problemele 6 and 7, nu este permisa
; conversia intre tipuri - se vor folosi metode
; directe.

(DEFUN subarbore-aux (N S L)
       (COND
        ((NULL L) NIL)
        ((AND (<= N 0) (> S 0))
         (subarbore-aux 1 (- S 1) L))
        ((AND (<= N 0) (<= S 0))
         NIL)
        ((AND (> N 0) (> S 0))
         (subarbore-aux (+ (- N 1) (CADR L)) S (CDDR L)))
        ((AND (> N 0) (<= S 0))
         (CONS
          (CAR L)
          (CONS
           (CADR L)
           (subarbore-aux (+ (- N 1) (CADR L)) S (CDDR L)))))))

(DEFUN subarbore (S L) (subarbore-aux 1 S L))

; 01. Se da un arbore de tipul (1). Sa se afiseze
;     calea de la radacina pana la un nod dat.

(DEFUN tema-1-cauta (E L)
       (COND
        ((NULL L) NIL)
        ((EQ (CAR L) E) T)
        ((tema-1-cauta E (subarbore 0 (CDDR L))) T)
        ((tema-1-cauta E (subarbore 1 (CDDR L))) T)
        (T NIL)))

(DEFUN tema-1 (E L)
       ((LAMBDA (ST DR)
                (COND
                 ((EQ (CAR L) E) (CONS (CAR L) NIL))
                 ((tema-1-cauta E ST)
                  (CONS (CAR L) (tema-1 E ST)))
                 ((tema-1-cauta E DR)
                  (CONS (CAR L) (tema-1 E DR)))
                 (T NIL)))
        (subarbore 0 (CDDR L))
        (subarbore 1 (CDDR L))))

; 02. Sa se tipareasca lista nodurilor de pe nivelul
;     k dintr-un arbore de tipul (1).

(DEFUN tema-2-aux (Level L)
       ((LAMBDA
         (ST DR)
         (COND
          ((NULL L) NIL)
          ((= Level 0) (CONS (CAR L) NIL))
          (T
           (APPEND
            (tema-2-aux (- Level 1) ST)
            (tema-2-aux (- Level 1) DR)))))
        (subarbore 0 (CDDR L))
        (subarbore 1 (CDDR L))))

(DEFUN tema-2 (Level L)
       (tema-2-aux (- Level 1) L))

; 03. Se da un arbore de tipul (1). Sa se precizeze
;     numarul de niveluri din arbore.



; 04. Sa se converteasca un arbore de tipul (2) la
;     un arbore de tipul (1).

; 1. (A 2 B 0 C 2 D 0 E 0)
; 2. (A (B) (C (D) (E)))

(DEFUN tema-4 (L)
       (CONS
        (CAR L)
        (CONS
         (APPLY
          '+
          (MAPCAR #'(LAMBDA (_) 1) (CDR L)))
         (APPLY
          #'APPEND
          (MAPCAR #'tema-4 (CDR L))))))

; 05. Sa se intoarca adancimea la care se afla un
;     nod intr-un arbore de tipul (1).

(DEFUN tema-5 (E L)
       (COND
        ((NULL L) NIL)
        ((EQ (CAR L) E) 1)
        (T
         ((LAMBDA
           (ST DR)
           (COND
            ((NOT (NULL ST)) (+ ST 1))
            ((NOT (NULL DR)) (+ DR 1))
            (T NIL)))
         (tema-5 E (subarbore 0 (CDDR L)))
         (tema-5 E (subarbore 1 (CDDR L)))))))

; 06. Sa se construiasca lista nodurilor unui arbore
;     de tipul (1) parcurs in inordine.
; 07. Se da un arbore de tipul (1). Sa se precizeze
;     nivelul pe care apare un nod in arbore.
;     Nivelul radacinii se considera a fi 0.
; 08. Sa se construiasca lista nodurilor unuiarbore
;     de tipul (2) parcurs in inordine.
; 09. Sa se converteasca un arbore de tipul (1) la
;     un arbore de tipul (2).
; 10. Se da un arbore de tipul (2). Sa se precizeze
;     nivelul pe care apare un nod in arbore.
;     Nivelul radacinii se considera a fi 0.
; 11. Se da un arbore de tipul (2). Sa se afiseze
;     nivelul (si lista corespunzatoarea nodurilor)
;     avand numar maxim de noduri. Nivelul radacinii
;     se considera 0.
; 12. Sa se construiasca lista nodurilor unui arbore
;     de tipul (2) parcurs in preordine.
; 13. Seda un arbore de tipul (2). Sa se afiseze
;     calea de la radacina pana la un nod dat.
; 14. Sa se construiasca lista nodurilor unui arbore
;     de tipul (2) parcurs in postordine.
; 15. Sa se construiasca lista nodurilor unui arbore
;     de tipul (1) parcurs in postordine.
; 16. Sa se decida daca un arbore de tipul (2) este
;     echilibrat (diferenta dintre adancimile celor
;     2 subarbori nu este mai mare decat 1).

(DEFUN tema-16-adancime (L)
       (COND
        ((NULL L) 0)
        ((LISTP L)
         (+
          (APPLY
           #'MAX
           (CONS
            0
            (MAPCAR
             #'tema-16-adancime
             (CDR L))))
          1))))

(DEFUN tema-16 (L)
       (COND
        (
         (AND
          (NOT (NULL (CDR L)))
          (NOT (NULL (CDDR L))))
         (AND
          (<=
           (ABS
            (-
             (tema-16-adancime (CADR L))
             (tema-16-adancime (CADDR L))))
           1)
          (tema-16 (CADR L))
          (tema-16 (CADDR L))))
        ((NOT (NULL (CDR L)))
         (tema-16 (CADR L)))
        (T T)))
