gen_aux([H|T], S, NP, R) :-
	S-H >= 0, H mod 2 =:= 0, S1 is S-H, NP1 is NP+1,
	gen_aux(T, S1, NP1, R1),
	R = [H|R1].
gen_aux([H|T], S, NP, R) :-
	S-H >= 0, H mod 2 =:= 1, S1 is S-H,
	gen_aux(T, S1, NP, R1),
	R = [H|R1].
gen_aux([_|T], S, NP, R) :-
	gen_aux(T, S, NP, R).
gen_aux([], 0, NP, []) :-
	NP mod 2 =:= 0.

gen(L, S, R) :-
	findall(R1, gen_aux(L, S, 0, R1), R).
