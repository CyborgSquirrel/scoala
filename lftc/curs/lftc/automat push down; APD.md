$M=(Q,\Sigma,\Gamma,\delta,q_0,Z_0,F)$

Unde:
- $Q$ - alfabetul stărilor
- $\Sigma$ - alfabetul de intrare
- $\Gamma$ - alfabetul memoriei stivă
- $q_0\in Q$ - stare inițială
- $Z_0\in\Gamma$ - simbolul de start al memoriei stivă
- $F\subseteq Q$ - mulțimea stărilor finale
- $\delta:Q\times(\Sigma\cup\{\varepsilon\})\times\Gamma\rightarrow\mathcal{P}(Q\times\Gamma^*)$ - funcția de tranziție