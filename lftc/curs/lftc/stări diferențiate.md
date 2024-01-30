![[automat finit; AF]]

Fie $q_1,q_2\in Q$ stări ale [[automat finit; AF|automatului finit]], și $x\in\Sigma^*$ o [[secvență; secvență peste sigma|secvență]].

$q_1$ și $q_2$ sunt **stări diferențiate** de $x$, dacă:
- din una dintre stări se poate ajunge cu $x$ la o stare finală, iar din cealalta nu se poate ajunge la nici o stare finală

Mai formal:
- $\exists q_f\in Q$ astfel încât $(q_1,x)\vdash^*(q_f,\varepsilon)$ și $\nexists q_f\in F$ astfel încât $(q_2,x)\vdash^*(q_f,\varepsilon)$
- sau, $\exists q_f\in Q$ astfel încât $(q_2,x)\vdash^*(q_f,\varepsilon)$ și $\nexists q_f\in F$ astfel încât $(q_1,x)\vdash^*(q_f,\varepsilon)$
