[[gramatică LL(k)]]

# Tabelul de analiză

Pe linia $X\in(N\cup\Sigma\cup\{\$\})$ coloana $a\in(N\cup\{\$\})$ va fi:
- $(\alpha, i)$, dacă:
	- $X\rightarrow\alpha\in P$, a $i$-a producție
	- $a\in\text{FIRST}_1(\alpha)$
- $(\alpha,i)$, dacă:
	- $X\rightarrow\alpha\in P$ a $i$-a producție
	- $\varepsilon\in\text{FIRST}_1(\alpha)$
	- $a\in\text{FOLLOW}_1(X)$
- $\text{acc}$, dacă: $X=\$$ și $a=\$$
- $\text{pop}$, dacă: $X=a$
- $\text{err}$, altfel

# Exemplu

Pentru gramatica:
$$
\begin{align}
S&\rightarrow bLe &(1) \\
S&\rightarrow i &(2) \\
L&\rightarrow ST &(3) \\
T&\rightarrow \varepsilon &(4) \\
T&\rightarrow pL &(5) \\
\end{align}
$$

[[FIRST și FOLLOW|Se calculează]] $\text{FIRST}_1$ și $\text{FOLLOW}_1$:

|  | $\text{FIRST}_1$ | $\text{FOLLOW}_1$ |
| ---- | ---- | ---- |
| $S$ | $b$,$i$ | $\$$,$p$,$e$ |
| $L$ | $b$,$i$ | $e$ |
| $T$ | $\varepsilon$,$p$ | $e$ |

Tabelul va fi:

![[tabelul de analiză LL(1) 2024-01-31 11.38.45.excalidraw]]

Pentru șirul: $bipie$

Analiza va fi:
$$
\begin{align}
&(bipie\$,S\$,\varepsilon) \\
\vdash&(bipie\$,bLe\$,1) \\
\vdash&(ipie\$,Le\$,1) \\
\vdash&(ipie\$,STe\$,13) \\
\vdash&(ipie\$,iTe\$,132) \\
\vdash&(pie\$,Te\$,132) \\
\vdash&(pie\$,pLe\$,1325) \\
\vdash&(ie\$,Le\$,1325) \\
\vdash&(ie\$,STe\$,13253) \\
\vdash&(ie\$,iTe\$,132532) \\
\vdash&(e\$,Te\$,132532) \\
\vdash&(e\$,e\$,1325324) \\
\vdash&(\$,\$,1325324) \\
\vdash&\text{acc} \\
\end{align}
$$
