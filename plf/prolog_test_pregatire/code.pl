min([H], H) :- !.

min([H|T], M) :-
	min(T, M),
	M < H,
	!.

min([H|T], H) :-
	min(T, _).

bye(E, [E|T], T) :- !.

bye(E, [H|T], R) :-
	bye(E, T, RN),
	R = [H|RN].

better_sort([], []) :- !.

better_sort(L, R) :-
	min(L, M),
	bye(M, L, LN),
	better_sort(LN, RN),
	R = [M|RN].

% Dandu-se o lista liniara nuerica, sa se stearga toate
% secventele de valori consecutive

% [1,2,4,6,7,8,10] -> [4,10]


schema([H1,H2|T], R, _) :-
	H1 is H2-1,
	!,
	schema([H2|T], R, 1).

schema([_|T], R, 1) :-
	schema(T, R, 0).

schema([H|T], R, 0) :-
	schema(T, RN, 0),
	R = [H|RN].

schema([], [], _).

% Dandu-se o lista liniara nuerica, sa se stearga toate
% secventele de valori consecutive

% [1,2,4,6,7,8,10] -> [4,10]

cheia_primara([H1,H2,H3|T], R) :-
	H1 is H2-1,
	H2 is H3-1,
	!,
	cheia_primara([H2,H3|T], R).

cheia_primara([H1,H2], R) :-
	H1 is H2-1,
	!,
	R = [].

cheia_primara([H1,H2,H3|T], R) :-
	H1 is H2-1,
	!,
	cheia_primara([H3|T], R).

cheia_primara([H|T], R) :-
	cheia_primara(T, RN),
	R = [H|RN].

cheia_primara([], []).

% Sa se determine cea mai lunga secventa de numere pare
% consecutive dintr-o lista (daca sunt mai multe secvente
% de lungime maxima, una dintre ele)

p15_get([H|T], V, R, S) :-
	V is H mod 2,
	!,
	p15_get(T, V, RN, S),
	R = [H|RN].

p15_get(L, _, [], L).

p15_len([], 0).

p15_len([_|T], R) :-
	p15_len(T, RN),
	R is RN+1.

p15_schema(V, _, Cond, V) :- Cond.
p15_schema(_, V, Cond, V) :- \+ Cond.

p15_sol([], []) :- !.

p15_sol(C, M) :-
	p15_get(C, 0, E, C1),
	p15_get(C1, 1, _, C2),
	p15_sol(C2, MN),
	p15_len(E, L1), p15_len(MN, L2),
	p15_schema(E, MN, L1 > L2, M).

hex( 0, '0').
hex( 1, '1').
hex( 2, '2').
hex( 3, '3').
hex( 4, '4').
hex( 5, '5').
hex( 6, '6').
hex( 7, '7').
hex( 8, '8').
hex( 9, '9').
hex(10, 'A').
hex(11, 'B').
hex(12, 'C').
hex(13, 'D').
hex(14, 'E').
hex(15, 'F').
