[[automat push down; APD]]

Automatul este **determinist**, dacă:

$\forall q\in Q,a\in\Sigma,Z\in\Gamma$
- fie, $\delta(q,\varepsilon,Z)=0$ și $\delta(q,a,Z)\le1$
- fie, $\delta(q,\varepsilon,Z)=1$ și $\delta(q,a,Z)=0$

Altfel, automatul este **nedeterminist**.

În alte **cuvinte**, automatul este determinist, dacă pentru toate perechile de (stare, stare stivă) există fie o tranziție cu epsilon, fie cel mult câte o tranziție cu fiecare simbol.