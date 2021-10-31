# https://docs.google.com/document/d/1EVePCa2MI6Y7PdsyDmHdHDaJtGRqTJTT6aIls84jwtk/edit?usp=sharing

from ui import meniu, eroare
import datetime

apartamente = {}
apartamente = {1: [[100.0, 'apa', datetime.date(2021, 10, 31)]], 2: [[123.0, 'canal', datetime.date(2021, 10, 31)]], 5: [[23232.0, 'gaz', datetime.date(2021, 10, 15)]]}
operatii = []

while True:
	for i,v in meniu.items():
		for j in range(i.count('.')):
			print("\t", end='')
		print(f"{i} {v[1]}")
	
	alegere = input("# ")
	try:
		meniu[alegere][0](apartamente, operatii)
	except (ValueError, IndexError, TypeError):
		eroare("Alegere invalida")
	finally:
		input("Apasati enter ca sa continuati ")
		print("")