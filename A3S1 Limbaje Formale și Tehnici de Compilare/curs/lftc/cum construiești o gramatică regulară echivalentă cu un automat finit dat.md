Pentru fiecare stare, iei toate tranzițiile. Pentru toate tranzițiile pui o regulă de producție $\textit{stare}\rightarrow\textit{stare\_nouă}\:\textit{simbol}$. Dacă $\textit{stare\_nouă}$ este o stare finală, se adaugă și regula de producție $\textit{stare}\rightarrow\textit{simbol}$

Exemplu:

![[cum construiești o gramatică regulară echivalentă cu un automat finit dat 2024-01-30 10.21.53.excalidraw]]

$$
\begin{align}
A&\rightarrow a \\
A&\rightarrow b \\
A&\rightarrow aB \\
A&\rightarrow bC \\
\\
B&\rightarrow aB \\
B&\rightarrow bC \\
B&\rightarrow a \\
B&\rightarrow b \\
\\
C&\rightarrow bC \\
C&\rightarrow b
\end{align}
$$