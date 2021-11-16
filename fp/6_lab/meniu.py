# https://docs.google.com/document/d/1EVePCa2MI6Y7PdsyDmHdHDaJtGRqTJTT6aIls84jwtk/edit?usp=sharing

from comanda import executa_comanda

apartamente = {}
operatii = []
	
while True:
	comanda = input("# ")
	comanda = comanda.split()
	
	arg = comanda[1:]
	comanda = comanda[0]
	
	executa_comanda(comanda, arg, apartamente, operatii)