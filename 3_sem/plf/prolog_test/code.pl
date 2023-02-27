% reversed_aux(L, Acc, Rev)
% modele de flux: (i, i, o), (i, i, i)
% L - lista care va fi inversata
% Acc - lista in care se construieste lista inversata
% Rev - lista inversata

reversed_aux([], Rev, Rev).

reversed_aux([H|T], Acc, Rev) :-
	reversed_aux(T, [H|Acc], Rev).

% reversed(L, Rev)
% modele de flux: (i, o), (i, i)
% L - lista care va fi inversata
% Rev - lista inversata

reversed(L, Rev) :-
	reversed_aux(L, [], Rev).

% sub_aux_2(L, Subbed, Ret)
% L - lista rezultata in urma apelarii sub_aux
% Subbed - cifra curenta
% Ret - numarul

sub_aux_2([], 0, []) :- !.
sub_aux_2(L, Subbed, [Subbed|L]).

% sub_aux(Num, Sub, Ret)
% modele de flux: (i, i, o), (i, i, i)
% Num - numarul, sub forma de lista inversata, din care se va scadea cifra Sub
% Sub - cifra care se va scadea din Num
% Ret - rezultatul scaderii

sub_aux([], 0, []).

sub_aux([H|T], Sub, Ret) :-
	Subbed is H-Sub,
	Subbed < 0,
	!,
	Subbed2 is Subbed+10,
	sub_aux(T, 1, Ret2),
	Ret = [Subbed2|Ret2].

sub_aux([H|T], Sub, Ret) :-
	Subbed is H-Sub,
	Subbed >= 0,
	sub_aux(T, 0, Ret2),
	!,
	sub_aux_2(Ret2, Subbed, Ret).

% sub(Num, Sub, Ret)
% modele de flux: (i, i, o), (i, i, i)
% Num - numarul, sub forma de lista, din care se va scadea cifra Sub
% Sub - cifra care se va scadea din Num
% Ret - rezultatul scaderii

sub(Num, Sub, Ret) :-
	reversed(Num, NumRev),
	sub_aux(NumRev, Sub, RetRev),
	reversed(RetRev, Ret).

test_sub :-
	sub([1, 5], 3, [1, 2]),
	sub([1, 5], 6, [9]),
	sub([5], 5, []).
