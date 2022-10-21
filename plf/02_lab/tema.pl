% 6.

% a. Sa se scrie un predicat care elimina dintr-o lista
% toate elementele care se repeta
% (ex: l=[1,2,1,4,1,3,4] => l=[2,3])

remove_count(_, [], RetCount, RetList) :- 
	RetCount=0,
	RetList=[].

remove_count(A, [B | List], RetCount, RetList) :-
	A =:= B,
	remove_count(A, List, RetCount2, RetList),
	RetCount is RetCount2+1.

remove_count(A, [B | List], RetCount, RetList) :-
	A =\= B,
	remove_count(A, List, RetCount, RetList2),
	append([B], RetList2, RetList).

remove_repeating([], RetList) :- RetList=[].

remove_repeating([A | List], RetList) :-
	remove_count(A, List, RemoveCount, RemoveList),
	RemoveCount is 0,
	remove_repeating(RemoveList, RemoveRepeatingList),
	append([A], RemoveRepeatingList, RetList).

remove_repeating([A | List], RetList) :-
	remove_count(A, List, RemoveCount, RemoveList),
	RemoveCount > 0,
	remove_repeating(RemoveList, RetList).

% b. Sa se elimine toate aparitiile elementului maxim
% dintr-o lista de numere intregi.

find_max([A], A) :- !.

find_max([A | List], RetMax) :-
	find_max(List, NewMax),
	A >= NewMax,
	RetMax is A.

find_max([A | List], RetMax) :-
	find_max(List, NewMax),
	A < NewMax,
	RetMax is NewMax.

remove_element(_, [], []) :- !.

remove_element(Elem, [A | List], RetList) :-
	A =:= Elem,
	remove_element(Elem, List, RetList).

remove_element(Elem, [A | List], RetList) :-
	A =\= Elem,
	remove_element(Elem, List, RetList2),
	append([A], RetList2, RetList).

remove_max(List, RetList) :-
	find_max(List, Max),
	remove_element(Max, List, RetList).
