"""
Să se determine numărul format prin însumarea elementelor de ordin
par ale unei liste, din care se scad elementele de ordin impar ale listei.
"""

from lista import Lista, tipar, creareLista


def f(lista, i):
	if lista is None:
		return 0
	else:
		if i%2 == 0:
			return f(lista.urm, i+1) + lista.e
		else:
			return f(lista.urm, i+1) - lista.e


def main():
	lista = creareLista()
	rezultat = f(lista.prim, 1)
	tipar(lista)
	print(rezultat)


if __name__ == "__main__":
	main()
