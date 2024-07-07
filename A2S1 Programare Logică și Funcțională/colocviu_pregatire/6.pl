genereaza_aux([H|T], S, NP, R) :-
	H mod 2 =:= 0, S1 is S+H, NP1 is NP+1,
	genereaza_aux(T, S1, NP1, R1),
	R = [H|R1].
genereaza_aux([H|T], S, NP, R) :-
	H mod 2 =:= 1, S1 is S+H,
	genereaza_aux(T, S1, NP, R1),
	R = [H|R1].
genereaza_aux([_|T], S, NP, R) :-
	genereaza_aux(T, S, NP, R).
genereaza_aux([], S, NP, []) :-
	S mod 2 =:= 1, NP > 0, NP mod 2 =:= 0.

genereaza(L, R) :-
	findall(R1, genereaza_aux(L, 0, 0, R1), R).
