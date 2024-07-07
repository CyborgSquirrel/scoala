[[gramatică]]

- **L**eft to right
- **R**ightmost derivation
- **k** - numărul de terminali de look-ahead

analiză sintactică ascendentă

O gramatică este **LR(k)**, pentru $k\ge 0$, dacă și numai dacă:

Din:
- $S'\overset{*}{\Rightarrow}_{\text{dr}}\alpha Aw\overset{*}{\Rightarrow}_{\text{dr}}\alpha\beta w$
- $S'\overset{*}{\Rightarrow}_{\text{dr}}\gamma Bx\overset{*}{\Rightarrow}_{\text{dr}}\alpha\beta y$
- $\text{FIRST}_k(w)=\text{FIRST}_k(y)$
Rezultă că:
- $A=B$
- $x=y$
- $\alpha=\gamma$