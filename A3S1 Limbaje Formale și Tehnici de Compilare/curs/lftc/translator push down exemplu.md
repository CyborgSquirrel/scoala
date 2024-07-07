[[translator push down]]
$$
\{a^n\mid n\ge1\}\Rightarrow\{a^nb^n\mid n\ge1\}
$$

$$
\begin{align}
Q&=\{q_0,q_1,q_2\} \\
\Sigma&=\{a\} \\
\Gamma&=\{Z,A\} \\
D&=\{a,b\} \\
q_0&=q_0 \\
Z_0&=Z \\
\\
\delta(q_0,a,Z)&=\{(q_1,A,a)\} \\
\delta(q_1,a,A)&=\{(q_1,AA,a)\} \\
\delta(q_1,\varepsilon,A)&=\{(q_2,A,\varepsilon)\} \\
\delta(q_2,\varepsilon,A)&=\{(q_2,\varepsilon,b)\} \\
\delta(.,.,.)&=\emptyset \\
\end{align}
$$

$$
\begin{align}
&(q_0,aa,Z,\varepsilon) \\
\vdash&(q_1,a,A,a) \\
\vdash&(q_1,\varepsilon,AA,aa) \\
\vdash&(q_2,\varepsilon,AA,aa) \\
\vdash&(q_2,\varepsilon,A,aab) \\
\vdash&(q_2,\varepsilon,\varepsilon,aabb) \\
\end{align}
$$