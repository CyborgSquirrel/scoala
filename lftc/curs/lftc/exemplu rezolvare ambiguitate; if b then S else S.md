Gramatica ambiguă:
$$
\begin{align}
S&\rightarrow\text{if}\:\text{b}\:\text{then}\:S\:\text{else}\:S \\
S&\rightarrow\text{if}\:\text{b}\:\text{then}\:S \\
S&\rightarrow\text{stmt} \\
\end{align}
$$
Gramatica neambiguă:
$$
\begin{align}
A&\rightarrow\text{if}\:\text{b}\:\text{then}\:A \\
A&\rightarrow\text{stmt}\:B \\
A&\rightarrow\text{stmt} \\
B&\rightarrow\text{else}\:A \\
\end{align}
$$