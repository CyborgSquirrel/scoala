% 6.

% a. Sa se scrie un predicat care elimina dintr-o lista
% toate elementele care se repeta
% (ex: l=[1,2,1,4,1,3,4] => l=[2,3])

% remove(i, i, o)

remove(_, [], []).

remove(A, [A | List], RetList) :-
	!, remove(A, List, RetList).

remove(A, [H | List], [H | RetList]) :-
	remove(A, List, RetList).

% count(i, i, o)

count(_, [], 0).

count(A, [A | List], RetCount) :-
	!,
	count(A, List, RetCount2),
	RetCount is RetCount2+1.

count(A, [_ | List], RetCount) :-
	count(A, List, RetCount).

% remove_repeating(i, o)

remove_repeating([], []).

remove_repeating([A | List], [A | RetList]) :-
	count(A, List, 0),
	remove_repeating(List, RetList).

remove_repeating([A | List], RetList) :-
	count(A, List, Count),
	Count > 0,
	remove(A, List, RemoveList),
	remove_repeating(RemoveList, RetList).

% tests

remove_repeating_1(RetList) :-
	remove_repeating([1,1,1,1,1,1,1], RetList).
remove_repeating_2(RetList) :-
	remove_repeating([], RetList).
remove_repeating_3(RetList) :-
	remove_repeating([13,67,76,86,43,57], RetList).
remove_repeating_4(RetList) :-
	remove_repeating([a,b,a,b,c], RetList).
remove_repeating_5(RetList) :-
	remove_repeating([3,4,3,3,2,5,3,3,4,5,5,3], RetList).

% b. Sa se elimine toate aparitiile elementului maxim
% dintr-o lista de numere intregi.

% find_max(i, o)

find_max([A], A).

find_max([A | List], RetMax) :-
	find_max(List, NewMax),
	A >= NewMax,
	RetMax is A.

find_max([A | List], RetMax) :-
	find_max(List, NewMax),
	A < NewMax,
	RetMax is NewMax.

% remove_max(i, o)

remove_max(List, RetList) :-
	find_max(List, Max),
	remove(Max, List, RetList).

% tests

remove_max_1(RetList) :-
	remove_max([1,2,1,4,1,3,4], RetList).
remove_max_2(RetList) :-
	remove_max([3,4,3,3,2,5,3,3,4,5,5,3], RetList).
remove_max_3(RetList) :-
	remove_max([6,9,4,6,1], RetList).
remove_max_4(RetList) :-
	remove_max([], RetList).
remove_max_5(RetList) :-
	remove_max([1, 1, 1, 1, 1, 1], RetList).
