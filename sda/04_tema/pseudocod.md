Fie $D=\left\{d\mid d\text{ este }DO\text{ cu cheia }TCheie\text{, valoarea }TValoare\text{, si relatia }r\right\}$

pre: $d\in D$, $c:TCheie\mapsto \{A,F\}$ \
post: $d'=\{e\in d\mid c(e.cheie)=A\}$ \
complexitate: $\Theta(n)$

SubAlgoritm filtreaza(d^i,o^, c^i^) \
\	p ← &d.prim \
\	CatTimp [p] $\ge$ 0 executa \
\	\	pi ← [p] \
\	\	Daca !c(d.e[pi].elem.cheie) atunci \
\	\	\	d.dim ← d.dim - 1 \
\	\	\	urm ← d.e[pi].urm \
\	\	\	d.e[pi] ← NIL \
\	\	\	[p] ← urm \
\	\	Altfel \
\	\	\	p ← &d.e[pi].urm \
\	\	SfDaca \
SfSubAlgoritm
