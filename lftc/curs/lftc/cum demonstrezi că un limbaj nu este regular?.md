Folosești negația lemei de pompare.
![[lema de pompare pentru limbaje regulare|lemei de pompare pentru limbaje regulare]]

Exemplu:

$L=\{a^nb^{2n}\mid n\in\mathbb{N}^*\}$

$\forall p\in\mathbb{N}^*,\exists w=a^pb^{2p},|w|=3p\ge p$

Demonstrăm că pentru orice descompunere $w=xyz,0\lt|y|\le p$, se poate găsi un $i$ astfel încât $xy^iz\notin L$

1. Descompunere:
   $$
   \begin{align}
   x&=a^m &&0\le m\lt p \\
   y&=a^n &&0\lt n\le p \\
   z&=a^{p-m-n}b^{2p} && \\
   \end{align}
   $$
   $$
   \begin{align}
   i=0\Rightarrow xy^iz&=a^ma^{p-m-n}b^{2p}\\&=a^{p-n}b^{2p}\notin L,\text{pentru că }p-n\ne p,\text{pentru că }n\gt0
   \end{align}
   $$
2. Descompunere:
   $$
   \begin{align}
   x&=a^{p-m} &&\\
   y&=a^mb^n &&0\lt m ,0\lt n,m+n\le p \\
   z&=b^{2p-n} && \\
   \end{align}
   $$
   $$
   \begin{align}
   i=2\Rightarrow xy^iz&=a^{p-m}(a^mb^n)^2b^{2p-n}\\&=a^{p-m}a^mb^na^mb^nb^{2p-n}\\&=a^pb^na^mb^{2p}\notin L
   \end{align}
   $$
3. Descompunere:
   $$
   \begin{align}
   x&=a^pb^m && 0\le m\lt p \\
   y&=b^n && 0\lt n\le p\\
   z&=b^{2p-m-n} \\
   \end{align}
   $$
   $$
   \begin{align}
   i=0\Rightarrow xy^iz&=a^pb^mb^{2p-m-n}\\&=a^pb^{2p-n}\notin L,\text{pentru că }2p-n\ne 2p,\text{pentru că }n\gt0
   \end{align}
   $$
Așadar, [[lema de pompare pentru limbaje regulare|lema de pompare]] nu are loc, deci limbajul nu este [[limbaj regular|regular]].