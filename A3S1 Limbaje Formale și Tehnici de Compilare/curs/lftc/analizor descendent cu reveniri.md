Automat: $(\text{stare},\text{poziție\_curentă},[\text{stiva\_de\_lucru},\text{stiva\_de\_intrare}])$

Configurație inițială: $(q,1,\varepsilon,S)$

Stări:
- $q$ - stare normală
- $r$ - stare de revenire
- $t$ - stare de terminare cu succes
- $e$ - stare de eroare

# Exemplu

Gramatica:
$$
\begin{align}
S&\rightarrow aSbS &(S_1) \\
S&\rightarrow aS &(S_2) \\
S&\rightarrow c &(S_3) \\
\end{align}
$$
Șirul: $acbc$

Analiza:
$$
\begin{align}
&(q,1,S,\varepsilon) \\
\vdash&(q,1,S_1,aSbS) \\
\vdash&(q,2,S_1a,SbS) \\
\vdash&(q,2,S_1aS_1,aSbSbS) \\
\vdash&(r,2,S_1aS_1,aSbSbS) \\
\vdash&(q,2,S_1aS_2,aSbS) \\
\vdash&(r,2,S_1aS_2,aSbS) \\
\vdash&(q,2,S_1aS_3,cbS) \\
\vdash&(q,3,S_1aS_3c,bS) \\
\vdash&(q,4,S_1aS_3cb,S) \\
\vdash&(q,4,S_1aS_3cbS_1,aSbS) \\
\vdash&(r,4,S_1aS_3cbS_1,aSbS) \\
\vdash&(q,4,S_1aS_3cbS_2,aS) \\
\vdash&(r,4,S_1aS_3cbS_2,aS) \\
\vdash&(q,4,S_1aS_3cbS_3,c) \\
\vdash&(q,5,S_1aS_3cbS_3c,\varepsilon) \\
\vdash&(t,5,S_1aS_3cbS_3c,\varepsilon) \\
&\Rightarrow acbc\in L(G)
\end{align}
$$

Șirul: $cb$

Analiza:
$$
\begin{align}
&(q,1,S,\varepsilon) \\
\vdash&(q,1,S_1,aSbS) \\
\vdash&(r,1,S_1,aSbS) \\
\vdash&(q,1,S_2,aS) \\
\vdash&(r,1,S_2,aS) \\
\vdash&(q,1,S_3,c) \\
\vdash&(q,2,S_3c,\varepsilon) \\
\vdash&(r,2,S_3c,\varepsilon) \\
\vdash&(r,1,S_3,c) \\
\vdash&(e,1,\varepsilon,S) \\
&\Rightarrow cb\notin L(G)
\end{align}
$$