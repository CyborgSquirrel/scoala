![[gramatică]]

- $X\overset{\bullet}{=}Y$
	- $A\rightarrow \alpha XY\beta\in P$
		- $A\in N$
		- $\alpha,\beta\in(N\cup\Sigma)^*$
		- $X,Y\in(N\cup\Sigma)$
- $X\overset{\bullet}{\lt}Y$
	- $A\rightarrow\alpha XB\beta\in P$
	- $B\overset{+}{\Rightarrow}Y\gamma$
		- $A,B\in N$
		- $\alpha,\beta,\gamma\in(N\cup\Sigma)^*$
		- $X,Y\in(N\cup\Sigma)$
- $X\overset{\bullet}{\gt}Y$
	- $A\rightarrow\alpha BY\beta\in P$
	- $B\overset{+}{\Rightarrow}\gamma X$
	- $Y\overset{*}{\Rightarrow}a\delta$
		- $A,B\in N$
		- $\alpha,\beta,\gamma,\delta\in(N\cup\Sigma)^*$
		- $X,Y\in(N\cup\Sigma)$
		- $a\in\Sigma$
- $\$\overset{\bullet}{\lt}X$
	- $S\overset{+}{\Rightarrow}X\alpha$
		- $\alpha\in(N\cup\Sigma)^*$
		- $X\in(N\cup\Sigma)$
- $X\overset{\bullet}{\gt}\$$
	- $S\overset{+}{\Rightarrow}\alpha X$
		- $\alpha\in(N\cup\Sigma)^*$
		- $X\in(N\cup\Sigma)$

# Exemplu

Gramatica:

$$
\begin{align}
S&\rightarrow aSSb \\
S&\rightarrow c \\
\end{align}
$$
Tabel:

|  | $S$ | $a$ | $b$ | $c$ | $\$$ |
| ---- | ---- | ---- | ---- | ---- | ---- |
| $S$ | = |  | = | < |  |
| $a$ | = | < |  | < |  |
| $b$ |  |  |  |  |  |
| $c$ |  |  |  |  |  |
| $\$$ |  |  |  |  |  |
