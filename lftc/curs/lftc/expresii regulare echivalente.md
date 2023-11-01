[[mulțimi regulare; expresii regulare]]

reuniune și concatenare
- $r+s=s+r$
- $(r+s)+t=r+(s+t)$
- $(rs)t=r(st)$
- $(r+s)t=rt+rs$
- $r(s+t)=rs+rt$

$\Phi$ și $\varepsilon$
- $\Phi+r=r+\Phi=r$
- $\varepsilon r=r\varepsilon=r$
- $\Phi r=r\Phi=\Phi$

$\Phi$ și $\varepsilon$ cu $*$
- $\Phi^*=\varepsilon$
- $r^*+\varepsilon=\varepsilon+r^*=r^*$
- $(\varepsilon+r)^*=r^*$
- $(r^*)^*=r^*$
- $(r^*s^*)=(r+s)^*$

# De ce $\Phi r=r\Phi=\Phi$?

Pentru că concatenarea este definită ca fiind:
$$
ab=\left\{cd:c\in a,d\in b\right\}
$$
Iar în mulțimea $\Phi$ nu există nici un element.
# De ce $\Phi^*=\varepsilon$?

Pentru că operatorul $*$ adaugă implicit elementul $\varepsilon$, reprezentând 0 repetări. 