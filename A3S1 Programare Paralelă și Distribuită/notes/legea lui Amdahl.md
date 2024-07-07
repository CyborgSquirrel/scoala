
> [!NOTE]
> Se consideră că proporțiile calculului paralel și a calculului secvențial **nu depind** de dimensiunea datelor.

Fie:
- $p$ - numărul de procesoare
- $\text{seq}$ - proporția care este neapărat secvențială
- $\text{par}$ - proporția care poate fi paralelizată
- $\text{seq}+\text{par}=1$

Dacă considerăm că $T_1=\text{seq}+\text{par}$ și $T_p=\text{seq}+\frac{\text{par}}{p}$, atunci [[accelerare|accelerarea]] va fi:
$$
S_p=\frac{T_1}{T_p}=\frac{1}{\text{seq}+\frac{\text{par}}{p}}
$$
Dacă $p\rightarrow\infty$, atunci:
$$
S_p=\frac{1}{\text{seq}+\frac{\text{par}}{p}}\rightarrow\frac{1}{\text{seq}}
$$
Așadar, accelerarea maximă este invers proporțională cu proporția părții secvențiale. De exemplu, pentru $\text{seq}=0.20$, $S_p=\frac{1}{0.20}=5$.