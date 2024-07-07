[[gramatică LR(k)]]

# Colecția canonică

Element inițial: $[S'\rightarrow .S,\$]$.

Predicția este $\text{FIRST}_1$ din simbolurile după neterminalul după punct, urmate de predicția curentă.

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

Colecția canonică va fi:

![[colecția canonică și tabelul de analiză LR(1) 2024-01-30 18.19.33.excalidraw]]

La $I_0$, predicția lui $A\rightarrow.aA$ este $\text{FIRST}_1(A)$.
La $I_3$, predicția lui $A\rightarrow.aA$ este $\text{FIRST}_1(a)\cup\text{FIRST}_1(b)$.

Dacă aveam ceva de genul $[A\rightarrow a.AA,a|b]$, unde $\text{FIRST}_1(A)=\{a,b\}$, atunci predicția pentru $A\rightarrow .aAA$ ar fi fost $\text{FIRST}_1(Aa)\cup\text{FIRST}_1(Ab)=\{a,b\}$.

Tabelul de analiză ar fi:

![[colecția canonică și tabelul de analiză LR(1) 2024-01-30 18.43.50.excalidraw]]

Pentru șirul: $abb$

Analiza va fi:
$$
\begin{align}
&(\$0,abb\$,\varepsilon) \\
\vdash&(\$0a3,bb\$,\varepsilon) \\
\vdash&(\$0a3b4,b\$,\varepsilon) \\
\vdash&(\$0a3A8,b\$,3) \\
\vdash&(\$0A2,b\$,23) \\
\vdash&(\$0A2b7,\$,23) \\
\vdash&(\$0A2A5,\$,323) \\
\vdash&(\$0S1,\$,1323) \\
\vdash&\text{acc} \\
\end{align}
$$