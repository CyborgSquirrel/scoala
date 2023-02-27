insert_everywhere(E, L, [E|L]).
insert_everywhere(E, [H|T], O) :-
	insert_everywhere(E, T, O1),
	O = [H|O1].

perm([], []).
perm([H|T], P) :-
	perm(T, L),
	insert_everywhere(H, L, P).
