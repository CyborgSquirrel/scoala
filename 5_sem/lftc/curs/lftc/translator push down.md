$M=(Q,\Sigma,\Gamma,D,\delta,q_0,Z_0,F)$

Unde:
- $Q$ - alfabetul stărilor
- $\Sigma$ - alfabetul de intrare
- $\Gamma$ - alfabetul memoriei stivă
- $D$ - alfabetul de ieșire
- $\delta:Q\times(\Sigma\cup\{\varepsilon\})\times\Gamma\rightarrow\mathcal{P}_0(Q\times\Gamma^*\times D^*)$ - mulțimea părților finite
- $q_0\in Q$ - stare inițială
- $Z_0\in\Gamma$ - simbolul de start al memoriei stivă
- $F\subseteq Q$ - mulțimea stărilor finale