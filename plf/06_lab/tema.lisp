; arbori binari
;
;   A
;  / \
;  B  C
;    / \
;    D  E
;
; tipul (1)
; (A 2 B 0 C 2 D 0 E 0)

; 3. Se da un arbore de tipul (1). Sa se precizeze numarul
; de niveluri din arbore.

; tema-sub-aux(tree: List, sub: Int, current-node: Int, nodes-total: Int)
; tree         - arborele din care se va extrage subarborele de indice sub
; sub          - indicele subarborelui care va fi extras
; current-node - indicele nodului curent
; nodes-total  - numarul total de noduri

(DEFUN tema-sub-aux (tree sub current-node nodes-total)
       (COND
        ((>= current-node nodes-total)
         (COND
          ((> sub 0)
           (tema-sub-aux
            tree
            (- sub 1)
            0
            1))
          (T NIL)))
        (T
         (COND
          ((> sub 0)
           (tema-sub-aux
            (CDDR tree)
            sub
            (+ 1 current-node)
            (+ (CADR tree) nodes-total)))
          (T
           (CONS
            (CAR tree)
            (CONS
             (CADR tree)
             (tema-sub-aux
              (CDDR tree)
              sub
              (+ 1 current-node)
              (+ (CADR tree) nodes-total)))))))))

; tema-sub(tree: List, sub: Int)
; tree - arborele din care se va extrage subarborele de indice sub
; sub  - indicele subarborelui care va fi extras
(DEFUN tema-sub (tree sub) (tema-sub-aux tree sub 0 1))

; tema-levels-aux(tree: List, current-level: Int)
; tree          - arborele pentru care se va returna numarul de niveluri
; current-level - nivelul curent
(DEFUN tema-levels-aux (tree current-level)
       (COND
        ((= (CADR tree) 0) current-level)
        ((= (CADR tree) 1)
         (tema-levels-aux
          (CDDR tree)
          (+ 1 current-level)))
        ((= (CADR tree) 2)
         (max
          (tema-levels-aux
           (tema-sub (CDDR tree) 0)
           (+ 1 current-level))
          (tema-levels-aux
           (tema-sub (CDDR tree) 1)
           (+ 1 current-level))))))

; tema-levels(tree: List)
; tree - arborele pentru care se va returna numarul de niveluri
(DEFUN tema-levels (tree) (tema-levels-aux tree 1))

; 1    A
;     / \
; 2   B  C
;       / \
; 3     D  E
(ASSERT (= (tema-levels '(A 2 B 0 C 2 D 0 E 0)) 3))

; 1   A
(ASSERT (= (tema-levels '(A 0)) 1))

; 1      A
;       / \
; 2     B  E
;      /  / \
; 3    C  F  G
;     /
; 4   D
(ASSERT (= (tema-levels '(A 2 B 1 C 1 D 0 E 2 F 0 G 0)) 4))

; 1     A
;      / \
; 2    B  C
;     /  / \
; 3   H  D E
;      \  \
; 4    I  G
;     / \
; 5   J K
(ASSERT (= (tema-levels '(A 2 B 1 H 1 I 2 J 0 K 0 C 2 D 1 G 0 E 0)) 5))
