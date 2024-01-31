[[automat finit; AF]]

$M$ este **determinist** (AFD), dacă:
- $|\delta(q,a)|\le1,\forall q\in Q,a\in\Sigma$

$M$ este **nedeterminist** (AFN), dacă nu este determinist. Altfel spus, dacă:
- $\exists q\in Q,a\in\Sigma$ astfel încât $|\delta(q,a)\gt1|$

$M$ este **complet definit**, dacă:
- $|\delta(q,a)|=1,\forall q\in Q,a\in\Sigma$