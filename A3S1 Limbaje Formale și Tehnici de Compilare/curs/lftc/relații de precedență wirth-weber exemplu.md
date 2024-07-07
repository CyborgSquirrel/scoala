[[relații de precedență wirth-weber]]

Gramatica:

$$
\begin{align}
S&\rightarrow aSSb &(1) \\
S&\rightarrow c &(2) \\
\end{align}
$$
Mulțimi:
$$
\begin{align}
\text{Head}^+(a)&=\emptyset \\
\text{Head}^+(S)&=\{a,c\} \\
\text{Head}^+(b)&=\emptyset \\
\text{Head}^+(c)&=\emptyset \\
\\
\text{Tail}^+(a)&=\emptyset \\
\text{Tail}^+(S)&=\{b,c\} \\
\text{Tail}^+(b)&=\emptyset \\
\text{Tail}^+(c)&=\emptyset \\
\\
\text{Head}^*(a)&=\{a\} \\
\text{Head}^*(S)&=\{a,c\} \\
\text{Head}^*(b)&=\{b\} \\
\text{Head}^*(c)&=\{c\} \\
\end{align}
$$
Tabel:

|  | $S$ | $a$ | $b$ | $c$ | $\$$ |
| ---- | ---- | ---- | ---- | ---- | ---- |
| $S$ | $\overset{\bullet}{=}$ | $\overset{\bullet}{\lt}$ | $\overset{\bullet}{=}$ | $\overset{\bullet}{\lt}$ |  |
| $a$ | $\overset{\bullet}{=}$ | $\overset{\bullet}{\lt}$ |  | $\overset{\bullet}{\lt}$ |  |
| $b$ |  | $\overset{\bullet}{\gt}$ | $\overset{\bullet}{\gt}$ | $\overset{\bullet}{\gt}$ | $\overset{\bullet}{\gt}$ |
| $c$ |  | $\overset{\bullet}{\gt}$ | $\overset{\bullet}{\gt}$ | $\overset{\bullet}{\gt}$ | $\overset{\bullet}{\gt}$ |
| $\$$ |  | $\overset{\bullet}{\lt}$ |  | $\overset{\bullet}{\lt}$ |  |

Analiză pentru $accb$:
$$
\begin{align}
&(\$\overset{\overset{\bullet}{\lt}}{,}accb\$,\varepsilon) \\
\vdash&(\$\overset{\bullet}{\lt}a\overset{\overset{\bullet}{\lt}}{,}ccb\$,\varepsilon) \\
\vdash&(\$\overset{\bullet}{\lt}a\overset{\bullet}{\lt}c\overset{\overset{\bullet}{\gt}}{,}cb\$,\varepsilon) \\
\vdash&(\$\overset{\bullet}{\lt}a\overset{\bullet}{=}S\overset{\overset{\bullet}{\lt}}{,}cb\$,2) \\
\vdash&(\$\overset{\bullet}{\lt}a\overset{\bullet}{=}S\overset{\bullet}{\lt}c\overset{\overset{\bullet}{\gt}}{,}b\$,2) \\
\vdash&(\$\overset{\bullet}{\lt}a\overset{\bullet}{=}S\overset{\bullet}{=}S\overset{\overset{\bullet}{=}}{,}b\$,22) \\
\vdash&(\$\overset{\bullet}{\lt}a\overset{\bullet}{=}S\overset{\bullet}{=}S\overset{\bullet}{=}b\overset{\overset{\bullet}{\gt}}{,}\$,22) \\
\vdash&(\$\overset{\bullet}{=}S,\$,122) \\
\end{align}
$$