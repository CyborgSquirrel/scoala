fact(N, F) :-
	N =:= 0,
	F = 1.

fact(N, F) :-
	N > 0,
	fact(N-1, F2),
	F is N*F2.

member1(E, [E|_]) .
member1(E, [_|L]) :- member1(E, L).

member2(E, [E|_]) :- !.
member2(E, [_|L]) :- member2(E, L).

adauga(E, [], [E]).
adauga(E, [H|T], Ret) :-
	adauga(E, T, L),
	Ret = [H|L].

invers([], Col, Col).
invers([H|T], Out, Col) :- invers(T, Out, [H|Col]).
invers(List, Out) :- invers(List, Out, []).
