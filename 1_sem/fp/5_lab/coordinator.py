# https://docs.google.com/document/d/1EVePCa2MI6Y7PdsyDmHdHDaJtGRqTJTT6aIls84jwtk/edit?usp=sharing

from ui import meniu, eroare
import datetime

apartamente = {}
operatii = []

while True:
	for i,v in enumerate(meniu):
		print(f"{i+1}. {v[1]}")
	
	alegere = input("# ")
	try:
		meniu[int(alegere)-1][0](apartamente, operatii)
	except (ValueError, IndexError):
		eroare("Alegere invalida")
		continue
	
	input("Apasati enter ca sa continuati ")