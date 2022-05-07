Fie $D=\left\{d\mid d\text{ este }DO\text{ cu cheia }TCheie\text{, valoarea }TValoare\text{, si relatia }r\right\}$

pre: $p\in D$ \
post: $v\in TValoare,v=\begin{cases}\text{cea mai frecventa valoare},\text{d nu e vid} \\ \text{NULL\_TVALOARE},\text{d e vid}\end{cases}$ \
complexitate: $\Theta(n)$

SubAlgoritm ceaMaiFrecventaValoare(d^i^, v^o^) \
\	\	fr ← { } \
\	\	max ← (NULL\_TVALOARE, 0) \
\	\	p ← &d.prim \
\	\	CatTimp [p] $\ge$ 0 executa \
\	\	\	\	gasit ← 0 \
\	\	\	\	i ← 0 \
\	\	\	\	pi ← [p] \
\	\	\	\	CatTimp i < len(fr) si gasit = 0 executa \
\	\	\	\	\	\	Daca fr[i][0] = d.e[pi] atunci \
\	\	\	\	\	\	\	\	fr[i][1] ← fr[i][1] + 1 \
\	\	\	\	\	\	\	\	gasit ← 1 \
\	\	\	\	\	\	\	\	Daca fr[i][1] > max[1] atunci \
\	\	\	\	\	\	\	\	\	\	max = fr[i] \
\	\	\	\	\	\	\	\	SfDaca \
\	\	\	\	\	\	SfDaca \
\	\	\	\	SfCatTimp \
\	\	\	\	Daca gasit = 0 atunci \
\	\	\	\	\	\	fr ← fr $\cup$ {(d.e[pi], 1)} \
\	\	\	\	\	\	Daca 1 > max[1] atunci \
\	\	\	\	\	\	\	\	max = (d.e[pi], 1) \
\	\	\	\	\	\	SfDaca \
\	\	\	\	SfDaca \
\	\	\	\	p ← &d.e[pi].urm \
\	\	SfCatTimp \
\	\	v ← max[1] \
SfSubAlgoritm
