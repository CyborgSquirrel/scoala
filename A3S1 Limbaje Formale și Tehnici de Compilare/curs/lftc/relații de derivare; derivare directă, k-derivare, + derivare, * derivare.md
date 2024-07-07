![[gramatică]]

- **derivare directă**
  $\gamma\Rightarrow\delta$, dacă se poate aplica o regulă de producție pe o parte din $\gamma$, astfel încât să se obțină $\delta$
  
  Mai formal, dacă și numai dacă $\exists \gamma_1,\gamma_2,\alpha,\beta\in(N\cup\Sigma)^*$, astfel încât:
  - $(\alpha\rightarrow\beta)\in P$
  - $\gamma=\gamma_1\alpha\gamma_2$
  - $\delta=\gamma_1\beta\gamma_2$
- **$k$-derivare** ($\gamma\overset{k}{\Rightarrow}\delta$)
  O succesiune de $k$ derivări directe.
- **+ derivare** ($\gamma\overset{+}{\Rightarrow}\delta$)
  Dacă $\exists k\gt0$ astfel încât $\gamma\overset{k}{\Rightarrow}\delta$.
- **\* derivare** ($\gamma\overset{*}{\Rightarrow}\delta$)
  Dacă $\gamma=\delta$ sau $\gamma\overset{+}{\Rightarrow}\delta$.
  