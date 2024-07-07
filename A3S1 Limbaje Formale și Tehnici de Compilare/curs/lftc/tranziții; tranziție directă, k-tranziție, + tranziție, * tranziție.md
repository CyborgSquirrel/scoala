![[automat push down; APD]]

- **tranziție directă**
  $(q,aw,Z\alpha)\vdash(p,w,\gamma\alpha)$, dacă $\delta(q,a,Z)\ni(p,\gamma)$
  sau $(q,w,Z\alpha)\vdash(p,w,\gamma\alpha)$, dacă $\delta(q,\varepsilon,Z)\ni(p,\gamma)$
  
  Unde:
  - $p,q\in Q$
  - $a\in\Sigma$
  - $w\in\Sigma^*$
  - $Z\in\Gamma$
  - $\alpha,\gamma\in\Gamma^*$
- **$k$-tranziție** ($\overset{k}{\vdash}$)
- **+ tranziție** ($\overset{+}{\vdash}$)
- **\* tranziție** ($\overset{*}{\vdash}$)