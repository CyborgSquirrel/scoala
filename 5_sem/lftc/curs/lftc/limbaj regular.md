Este un [[limbaj generat de o gramatică|limbaj care poate fi generat]] de o [[gramatică regulară; gramatică de tip 3|gramatică regulară]].

Gramatica următoare nu este regulară:
$$
\begin{align}
A&\rightarrow\varepsilon \\
A&\rightarrow aA
\end{align}
$$

Însă limbajul generat de această gramatică este regular, pentru că poate fi generat de următoarea gramatică regulară:
$$
\begin{align}
S&\rightarrow\varepsilon \\
S&\rightarrow aA \\
A&\rightarrow aA \\
A&\rightarrow a \\
\end{align}
$$