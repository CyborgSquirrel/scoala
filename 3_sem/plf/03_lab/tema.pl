% 1.

% a) Definiti un predicat care determina suma a doua numere
% scrise in reprezentare de lista.

% inverse_aux(List: list, Acc: list, Inverse: list)
% modele de flux: (i, i, o), (i, i, i)
% List - lista care va fi inversata
% Acc - lista in care se va construi lista inversa
% Inverse - lista inversata

inverse_aux([], Inverse, Inverse).

inverse_aux([H|T], Acc, Inverse) :-
	inverse_aux(T, [H|Acc], Inverse).

% inverse(List: list, Inverse: list)
% modele de flux: (i, o), (i, i)
% List - lista care va fi inversata
% Inverse - lista inversata

inverse(List, Inverse) :- inverse_aux(List, [], Inverse).

% sum_aux(Num1: list, Num2: list, Sum: list, Rem: integer)
% modele de flux: (i, i, o, i), (i, i, i, i)
% Num1 - primul numar care va fi adunat
% Num2 - al doilea numar care va fi adunat
% Sum - suma celor doua numere
% Rem - restul adunarii precedente

sum_aux([H1|T1], [H2|T2], [H3|T3], Rem) :-
	Sum is (H1 + H2 + Rem),
	H3 is Sum mod 10,
	Rem2 is Sum // 10,
	sum_aux(T1, T2, T3, Rem2).

sum_aux([], [H2|T2], [H3|T3], Rem) :-
	Sum is (H2 + Rem),
	H3 is Sum mod 10,
	Rem2 is Sum // 10,
	sum_aux([], T2, T3, Rem2).

sum_aux([H1|T1], [], [H3|T3], Rem) :-
	Sum is (H1 + Rem),
	H3 is Sum mod 10,
	Rem2 is Sum // 10,
	sum_aux(T1, [], T3, Rem2).

sum_aux([], [], [], 0) :- !.

sum_aux([], [], [Rem], Rem).

% sum(Num1: list, Num2: list, Sum: list)
% modele de flux: (i, i, o), (i, i, i)
% Num1 - primul numar care va fi adunat
% Num2 - al doilea numar care va fi adunat
% Sum - suma celor doua numere

sum(Num1, Num2, Sum) :-
	inverse(Num1, Num1Inverse),
	inverse(Num2, Num2Inverse),
	sum_aux(Num1Inverse, Num2Inverse, SumInverse, 0),
	inverse(SumInverse, Sum).

sum_test :-
	sum([1,2,3], [4,5,7], [5,8,0]),
	sum([4,2,3], [9,9,9], [1,4,2,2]),
	sum([4,2,3], [0,0,0,0,9], [0,0,4,3,2]),
	sum([1,2,3,4], [0], [1,2,3,4]),
	sum([1,0], [9,9,9,9,9], [1,0,0,0,0,9]).

% b) Se da o lista eterogena, formata din numere intregi
% si liste de cifre. Sa se calculeze suma tuturor numerelor
% reprezentate de subliste. De ex: [1, [2, 3], 4, 5, [6, 7,
% 9], 10, 11, [1, 2, 0], 6] => [8, 2, 2].

% sum_sub(List: list, Sum: list)
% modele de flux: (i, o), (i, i)
% List - lista de intrare
% Sum - suma numerelor reprezentate prin subliste din list

sum_sub([], []).

sum_sub([H|T], Sum) :-
	is_list(H),
	!,
	sum_sub(T, Sum2),
	sum(Sum2, H, Sum).

sum_sub([_|T], Sum) :-
	sum_sub(T, Sum).

sum_sub_test :-
	sum_sub(
		[1, [2,3], 4, 5, [6,7,9], 10, 11, [1,2,0], 6],
		[8,2,2]
	),
	sum_sub(
		[1, [7,1,2,4], 3, 5, 4, 7, [2,7], 6, 9, [0], 7],
		[7,1,5,1]
	),
	sum_sub(
		[0, 1, 124, 53, 23],
		[]
	),
	sum_sub(
		[30, 36, 64, 18, 81, [9,9,1,7,6], 15, 48, 72, 13, 79],
		[9,9,1,7,6]
	),
	sum_sub(
		[0, [3,1,8,3], 5, 5, 9, [2,9], 9, 7, 0, [2,5,4,0,8,7], 2, [8,0], 0, 4],
		[2,5,7,3,7,9]
	).
