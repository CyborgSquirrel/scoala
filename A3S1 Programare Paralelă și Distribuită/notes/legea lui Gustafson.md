
> [!NOTE]
> Se consideră că proporțiile calculului paralel și a calculului secvențial **depind** de dimensiunea datelor.

Fie:
- $m$ - dimensiunea datelor
- $p$ - numărul de procesoare
- $\text{seq}(m)$ - proporția calculului secvențial
- $\text{par}(m)$ - proporția calculului paralel

Dacă considerăm că $T_1=\text{seq}(m)+\text{par}(m)$ și $T_p=\text{seq}(m)+\frac{\text{par}(m)}{p}$, atunci [[accelerare|accelerarea]] va fi:
$$
S_p=\frac{T_1}{T_p}=\frac{\text{seq}(m)+\text{par}(m)}{\text{seq}(m)+\frac{\text{par}(m)}{p}}
$$
Dacă $\text{seq}(m)\rightarrow0$, atunci:
$$
S_p=\frac{\text{seq}(m)+\text{par}(m)}{\text{seq}(m)+\frac{\text{par}(m)}{p}}\rightarrow\frac{\text{par}(m)}{\frac{\text{par}(m)}{p}}=p
$$

Așadar, în limită, accelerarea este liniară.

Demonstrația ciudată din curs:

Dacă considerăm că varianta paralelă se execută într-o unitate de timp $T_p=\text{seq}(m)+\text{par}(m)=1$, atunci [[accelerare|accelerarea]] va fi:
$$
\text{seq}{(m)}+p\cdot\text{par}(m)=\text{seq}(m)+p(1-\text{seq}(m))
$$
Dacă $\text{seq}(m)\to0$, atunci:
$$
\text{seq}(m)+p(1-\text{seq}(m))\to p
$$
