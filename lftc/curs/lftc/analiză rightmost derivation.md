Automat: $([\text{stiva\_de\_lucru},\text{stiva\_de\_intrare}],\text{stiva\_de\_ieșire}])$

Configurația inițială: $(\$0,w\$,\varepsilon)$

$T(\text{linie},\text{coloană})$

Tranziții:
- deplasare $(\$\gamma s_k,a_i\dots a_n\$,\Pi)\vdash(\$\gamma s_ka_is_m,a_{i+1}\dots a_n\$,\Pi)$, dacă:
	- $T(s_k,\text{acțiune})=\text{s}$
	- $T(s_k,a_i)=s_m$
- reducere$(\$\gamma s_{p-1}X_ps_p\dots X_ks_k,a_i\dots a_n\$,\Pi)\vdash(\$\gamma s_{p-1}As_m,a_i\dots a_n\$,L\Pi)$, dacă:
	- $T(s_k,\text{acțiune})=L$
	- există producția $A\rightarrow X_p\dots X_k$ cu numărul $L$
	- $T(s_{p-1},\text{acțiune})=\text{s}$
	- $T(s_{p-1},A)=s_m$
- acceptare $(\$0Ss_{acc},\$,\Pi)\vdash\text{acc}$
- eroare, atlfel