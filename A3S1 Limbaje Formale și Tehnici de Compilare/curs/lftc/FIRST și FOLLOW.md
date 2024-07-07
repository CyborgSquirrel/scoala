[[gramatică]]

> [!NOTE]
> $\text{FOLLOW}_1$ nu poate conține niciodată $\varepsilon$. $\text{FIRST}_1(\alpha)$ poate conține $\varepsilon$, dacă se întâmplă $\alpha\overset{*}{\Rightarrow}\varepsilon$.

> [!NOTE]
> În modul în care ne-a predat profesoara, $\$\in\text{FOLLOW}_1(S)$ întotdeauna. Îți imaginezi că există o producție $S'\rightarrow S\$$ datorită căreia se întâmplă asta.

# Exemplu

Pentru gramatica:
$$
\begin{align}
S&\rightarrow abA \\
S&\rightarrow\varepsilon \\
A&\rightarrow Saa \\
A&\rightarrow b \\
\end{align}
$$
Tabelul ar fi:

|  | $\text{FIRST}_1$ | $\text{FOLLOW}_1$ |
| ---- | ---- | ---- |
| $S$ | $\varepsilon$,$a$ | $\$,a$ |
| $A$ | $a$,$b$ | $\$,a$ |
# Exemplu

Pentru gramatica:
$$
\begin{align}
S&\rightarrow BA \\
A&\rightarrow +BA \\
A&\rightarrow \varepsilon \\
B&\rightarrow DC \\
C&\rightarrow *DC \\
C&\rightarrow \varepsilon \\
D&\rightarrow (S) \\
D&\rightarrow a\\
\end{align}
$$
Tabelul ar fi:

|  | $\text{FIRST}_1$ | $\text{FOLLOW}_1$ |
| ---- | ---- | ---- |
| $S$ | $($,$a$ | $\$$,$)$ |
| $A$ | $\varepsilon$,$+$ | $\$$,$)$ |
| $B$ | $($,$a$ | $\$$,$)$,$+$ |
| $C$ | $\varepsilon$,$*$ | $\$$,$)$,$+$ |
| $D$ | $($,$a$ | $\$$,$)$,$+$,$*$ |
