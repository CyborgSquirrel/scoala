Exemplu:

Limbajul $L$:
$$L=\{x^ny^n\mid n\in\mathbb{N}\}$$
Gramatica $G$:
$$
\begin{align}
A&\rightarrow\varepsilon &(1)\\
A&\rightarrow xAy &(2)\\
\end{align}
$$

Demonstrăm că $L(G)=L$:

1. $L\subseteq L(G)$
   $A\Rightarrow \varepsilon$
   
   p.p. $A\overset{*}{\Rightarrow}x^{n-1}y^{n-1}$
   dem. $A\overset{*}{\Rightarrow}x^ny^n$
   $A\overset{*}{\Rightarrow}x^{n-1}y^{n-1}$, așadar $A\overset{(2)}{\Rightarrow}xx^{n-1}y^{n-1}y=x^ny^n$
   Rezultă că $\forall x^ny^n\in L,x^ny^n\in L(G)$, deci $L\subseteq L(G)$
2. $L(G)\subseteq L$
   Demonstrăm că după exact $k$ derivări se obține fie $x^kAy^k$, fie $x^{k-1}y^{k-1}$.
   
   $A\overset{(1)}{\Rightarrow}\varepsilon=x^0y^0$
   $A\overset{(2)}{\Rightarrow}xAy=x^1Ay^1$
   
   p.p. $A\overset{k-1}{\Rightarrow}x^{k-2}y^{k-2}$ sau $A\overset{k-1}{\Rightarrow}x^{k-1}Ay^{k-1}$
   dem. $A\overset{k}{\Rightarrow}x^{k-1}y^{k-1}$ sau $A\overset{k}{\Rightarrow}x^kAy^k$
   
   $A\overset{k-1}{\Rightarrow}x^{k-1}Ay^{k-1}\overset{(1)}{\Rightarrow}x^{k-1}y^{k-1}$
   $A\overset{k-1}{\Rightarrow}x^{k-1}Ay^{k-1}\overset{(2)}{\Rightarrow}x^kAy^k$
   
   Rezultă că $A\overset{k}{\Rightarrow}x^{k-1}y^{k-1}$ sau $A\overset{k}{\Rightarrow}x^kAy^k$.
   $\forall k\ge1, x^{k-1}y^{k-1}\in L$, deci $L(G)\subseteq L$

$L\subseteq L(G)$ și $L(G)\subseteq L$, deci $L=L(G)$