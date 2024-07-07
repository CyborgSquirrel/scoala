from comanda import executa_comanda

'''
add 1 123 apa 2021-11-11 ; print ; mod 1 0 222 - - ; print ; report type_sum apa ; report type_sum ap ; report type_sum gaz ; erase apartment 1 ; print ; undo ; print
'''

apartamente = {}
operatii = []

comenzi = input()
comenzi = comenzi.split(';')
for comanda in comenzi:
	comanda = comanda.split()
	
	arg = comanda[1:]
	comanda = comanda[0]
	
	executa_comanda(comanda, arg, apartamente, operatii)