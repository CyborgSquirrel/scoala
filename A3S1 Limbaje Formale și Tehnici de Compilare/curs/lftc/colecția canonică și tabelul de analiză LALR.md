[[gramatică LALR]]
# Exemplu

Pentru gramatica (îmbogățită cu producția $S'\rightarrow S$):
$$
\begin{align}
S'&\rightarrow S &(0) \\
S&\rightarrow AA &(1) \\
A&\rightarrow aA &(2) \\
A&\rightarrow b &(3) \\
\end{align}
$$
Mai întâi se calculează $\text{FIRST}_1$:

|  | $\text{FIRST}_1$ |
| ---- | ---- |
| $S'$ | $a$,$b$ |
| $S$ | $a$,$b$ |
| $A$ | $a$,$b$ |

Colecția canonică LR(1) va fi:

![[colecția canonică și tabelul de analiză LR(1) 2024-01-30 18.19.33.excalidraw]]

Tabelul de analiză LR(1) ar fi:

![[colecția canonică și tabelul de analiză LR(1) 2024-01-30 18.43.50.excalidraw]]

Se pot fuziona:
- $I_8-I_9$
- $I_4-I_7$
- $I_3-I_6$

> [!NOTE]
> Nu sunt sigur care sunt criteriile exacte care permit fuzionarea a două stări...

Colecția canonică va fi:

![[colecția canonică și tabelul de analiză LALR 2024-01-30 19.24.25.excalidraw]]

Tabelul de analiză va fi:

![[colecția canonică și tabelul de analiză LALR 2024-01-30 19.30.32.excalidraw]]