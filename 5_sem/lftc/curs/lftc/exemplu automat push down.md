[[automat push down; APD]]

Limbaj:
$$
L=\{w\overset{\sim}{w}\mid w\in\{a,b\}^*,\overset{\sim}{w}\text{ e inversul lui }w\}
$$

Reprezentare graf:
![[exemplu automat push down 2024-01-31 19.05.34.excalidraw]]

Reprezentare tabelară:
![[exemplu automat push down 2024-01-31 19.10.03.excalidraw]]

Analiză pentru $abbbba$:
$$
\begin{align}
&(q,abbbba,Z) \\
\vdash&(q,bbbba,AZ) \\
\vdash&(q,bbba,BAZ) \\
\vdash&(q,bba,BBAZ) \\
\vdash&(p,bba,BBAZ) \\
\vdash&(p,ba,BAZ) \\
\vdash&(p,a,AZ) \\
\vdash&(p,\varepsilon,Z) \\
\vdash&(p,\varepsilon,\varepsilon) \\
&\Rightarrow abbbba\in L_\varepsilon(M) \\
\end{align}
$$