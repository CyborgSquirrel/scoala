[[gramatică]]

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

# Algoritm

Se construiesc următoarele mulțimi, pentru toate $X\in(N\cup\Sigma)$:
$$
\begin{align}
\text{Head}^+(X)&=\{Y|X\overset{+}{\Rightarrow}Y\alpha\} \\
\text{Tail}^+(X)&=\{Y|X\overset{+}{\Rightarrow}\alpha Y\} \\
\text{Head}^*(X)&=(\text{Head}^+(X)\cup\{X\})\cap\Sigma
\end{align}
$$

Pentru fiecare producție $A\rightarrow\alpha\in P$, pentru fiecare pereche de simboluri consecutive $XY$ din $\alpha$, se adaugă relațiile:
- $X\overset{\bullet}{=}Y$
- $X\overset{\bullet}{\lt}\text{Head}^+(Y)$
- $\text{Tail}^+(X)\overset{\bullet}{\gt}\text{Head}^*(Y)$

Se mai adaugă și:
- $\$\overset{\bullet}{\lt}\text{Head}^+(S)$
- $\text{Tail}^+(S)\overset{\bullet}{\gt}\$$

# Analiză

Automat: $([\text{stiva\_de\_lucru},\text{stiva\_de\_intrare}],\text{stiva\_de\_ieșire}])$

Configurație inițială: $(\$,w\$,\varepsilon)$