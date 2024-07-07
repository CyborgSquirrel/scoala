[[translator finit]]
$$
T(M)=\{(a^n,b^n)\mid n\ge1\}
$$

$$
\begin{align}
\Sigma&=\{a\} \\
D&=\{b\} \\
q_0&=q_0 \\
F&=\{q_1\} \\
\\
\delta(q_0,a)&=\{(q_1,b)\} \\
\delta(q_0,\varepsilon)&=\emptyset \\
\delta(q_1,a)&=\{(q_1,b)\} \\
\delta(q_1,\varepsilon)&=\emptyset \\
\end{align}
$$

$$
\begin{align}
&(q_0,aaa,\varepsilon) \\
\vdash&(q_1,aa,b) \\
\vdash&(q_1,a,bb) \\
\vdash&(q_1,\varepsilon,bbb) \\
&\Rightarrow(aaa,bbb)\in T(M) \\
\end{align}
$$