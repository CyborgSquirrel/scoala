Fie $k+1$ noduri $\{x_0,x_1,\dots,x_k\}$ distincte. Atunci polinomul lui Lagrange al nodului $j$ va fi:

$$
\begin{aligned}
l_j(x)&=\frac{x-x_0}{x_j-x_0}\dots\frac{x-x_{j-1}}{x_j-x_{j-1}}\frac{x-x_{j+1}}{x_j-x_{j+1}}\dots\frac{x-x_k}{x_j-x_k} \\
&=\prod_{\substack{0\le m\le k \\ m\ne j}}\frac{x-x_m}{x_k-x_m}
\end{aligned}
$$

Observații:
- datorită numărătorului, valoarea polinomului va fi $0$ pentru orice nod $x_m\ne x_j$
- datorită numitorului, valoarea polinomului va fi $1$ pentru $x_j$

Mai pe scurt:
$$
l_j(x_m)=
\begin{cases}
1,&m=j \\
0,&m\ne j \\
\end{cases}
$$
