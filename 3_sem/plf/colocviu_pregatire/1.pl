elem([H|T], RI, RL) :-
	RI = H,
	RL = T.

elem([H|T], RI, RL) :-
	elem(T, RI, RL1),
	RL = [H|RL1].

arp(L, C, N, S, R) :-
	elem(L, RI, RL),
	arp(RL, [RI|C], N+1, S+RI, R).

arp(_, C, N, S, R) :-
	N > 0,
	0 is N mod 2,
	1 is S mod 2,
	R = C.
