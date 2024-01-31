[[gramatică LR(k)]]

# Colecția canonică

Element inițial: $[S'\rightarrow .S]$.

Oricând apare un neterminal după punct, se adaugă toate regulile de producție care au neterminalul respectiv în stânga, cu punctul înaintea primului simbol.

Apoi se tot repetă acest proces, până când nu mai apare un neterminal nemaiîntâlnit după punct.

Apoi se face câte o săgeată pentru fiecare simbol care apare după un punct. În nodul spre care indică săgeata apar uhh bla bla bla.

# Exemplu

Pentru gramatica (îmbogățită cu producția $S'\rightarrow S$):
$$
\begin{align}
S'&\rightarrow S &(0) \\
S&\rightarrow AB &(1) \\
A&\rightarrow a &(2) \\
B&\rightarrow b &(3) \\
\end{align}
$$

Colecția canonică va fi:

![[colecția canonică LR(0) 2024-01-30 16.23.31.excalidraw]]

Tabelul de analiză va fi:

- **acc** apare oriunde ai $[S'\rightarrow S.]$
- **{n}** apare dacă ai producția cu numărul n
- **s** pare să apară în restul cazurilor?

![[colecția canonică și tabelul de analiză LR(0) 2024-01-30 16.37.14.excalidraw]]

Pentru șirul: $ab$

Analiza va fi:
$$
\begin{align}
&(\$0,ab\$,\varepsilon) \\
\vdash&(\$0a3,b\$,\varepsilon) \\
\vdash&(\$0A2,b\$,2) \\
\vdash&(\$0A2b5,\$,2) \\
\vdash&(\$0A2B4,\$,32) \\
\vdash&(\$0S1,\$,132) \\
\vdash&\text{acc} \\
\end{align}
$$