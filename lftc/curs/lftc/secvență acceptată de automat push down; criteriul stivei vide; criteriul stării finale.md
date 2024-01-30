![[automat push down; APD]]

- După **criteriul stivei vide**
  $L_\varepsilon(M)=\{w\mid w\in\Sigma^*,(q_0,w,Z_0)\overset{*}{\vdash}(q,\varepsilon,\varepsilon),q\in Q\}$
- După **criteriul stării finale**
  $L_f(M)=\{w\mid w\in\Sigma^*,(q_0,w,Z_0)\overset{*}{\vdash}(q,\varepsilon,\gamma),q\in F,\gamma\in\Gamma^*\}$