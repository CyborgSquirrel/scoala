candidat([H|T], H, T).
candidat([H|T], ER, [H|LR]) :-
	candidat(T, ER, LR).

perm_aux(L, [], R) :-
	candidat(L, ER, LR),
	perm_aux(LR, [ER], R).
perm_aux(L, [H|T], R) :-
	candidat(L, ER, LR),
	abs(ER-H) >= 2,
	perm_aux(LR, [ER,H|T], R).
perm_aux([], R, R).

perm_gen(N, R) :-
	N>0,
	!,
	N1 is N-1,
	perm_gen(N1, R1),
	R = [N|R1].
perm_gen(N, R) :-
	N =:= 0,
	R = [].

perm(N, R) :-
	perm_gen(N, PR),
	perm_aux(PR, [], R).

perm_fin(N, R) :-
	findall(PR, perm(N, PR), R).
