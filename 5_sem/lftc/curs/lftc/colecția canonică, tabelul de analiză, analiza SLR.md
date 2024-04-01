[[gramatică SLR]]

Chestiile au forma:
$[A\rightarrow\alpha.\beta,u]$, $u=\text{FOLLOW}_1(A),|u|=1$

# Exemplu

Pentru gramatica (îmbogățită cu producția $S'\rightarrow S$):

$$
\begin{align}
S'&\rightarrow S &(0) \\
S&\rightarrow Ax &(1) \\
S&\rightarrow By &(2) \\
A&\rightarrow a &(3) \\
B&\rightarrow a &(4) \\
\end{align}
$$

Mai întâi se calculează $\text{FIRST}_1$ și $\text{FOLLOW}_1$:

|  | $\text{FIRST}_1$ | $\text{FOLLOW}_1$ |
| ---- | ---- | ---- |
| $S'$ | $a$ | $\$$ |
| $S$ | $a$ | $\$$ |
| $A$ | $a$ | $x$ |
| $B$ | $a$ | $y$ |
Colecția canonică va fi:

![[colecția canonică și tabelul de analiză SLR 2024-01-30 17.10.34.excalidraw]]

Tabelul de analiză va fi:

- **s{n}** shiftare în starea n
- **r{n}** reducere cu producția numărul n

![[colecția canonică și tabelul de analiză SLR 2024-01-30 17.16.18.excalidraw]]

Pentru șirul: $ax$

Analiza va fi:
$$
\begin{align}
&(\$0,ax\$,\varepsilon) \\
\vdash&(\$0a4,x\$,\varepsilon) \\
\vdash&(\$0A2,x\$,3) \\
\vdash&(\$0A2x5,\$,3) \\
\vdash&(\$0S1,\$,13) \\
\vdash&\text{acc} \\
\end{align}
$$
