% 2. Fiind dat un numar n pozitiv, se cere sa se determine
% toate descompunerile sale ca suma de numere prime
% distincte.

% is_prime_aux(A, I)
% modele de flux: (i, i)
% determinist: da
% A - numarul pentru care se va verifica daca este prim
% I - indicele curent

is_prime_aux(1, _) :- !, fail.

is_prime_aux(A, A) :- !.

is_prime_aux(A, I) :-
	0 is A mod I,
	!, fail.

is_prime_aux(A, I) :-
	I2 is I+1,
	is_prime_aux(A, I2).

% is_prime(A)
% modele de flux: (i)
% determinist: da
% A - numarul pentru care se va verifica daca este prim
is_prime(A) :- is_prime_aux(A, 2).

test_is_prime :-
	\+ (is_prime(1)),
	is_prime(2),
	\+ (is_prime(4)),
	is_prime(3),
	is_prime(5),
	is_prime(7),
	\+ (is_prime(100)).

% prime_sum_aux(A, I, R)
% modele de flux: (i, i, o), (i, i, i)
% determinist: nu
% A - numarul pentru care se afla toate descompunerile ca suma de numere prime distincte
% I - numarul curent
% R - descompunerea lui A in suma de numere prime distincte

prime_sum_aux(0, _, []).

prime_sum_aux(A, I, R) :-
	I2 is I+1,
	A2 is A-I2,
	A2 >= 0,
	is_prime(I2),
	prime_sum_aux(A2, I2, R2),
	R = [I2|R2].

prime_sum_aux(A, I, R) :-
	I2 is I+1,
	A > I2,
	prime_sum_aux(A, I2, R).

% prime_sum(A, R)
% modele de flux: (i, o), (i, i)
% determinist: nu
% A - numarul pentru care se afla toate descompunerile ca suma de numere prime distincte
% R - descompunerea lui A in suma de numere prime distincte

prime_sum(A, R) :-
	prime_sum_aux(A, 1, R).

test_prime_sum :-
	prime_sum(20, [2, 5, 13]),
	prime_sum(20, [2, 7, 11]),
	prime_sum(20, [3, 17]),
	prime_sum(20, [7, 13]),
	prime_sum(5, [2, 3]),
	prime_sum(5, [5]).
