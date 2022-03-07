from datetime import date
def get_today():
	''' Returns the current date as a string in format dd.MM.yyyy
	output: str
	'''
	today = date.today()
	day = str(today.day)
	day = "0"*(2-len(day)) + day
	
	month = str(today.month)
	month = "0"*(2-len(month)) + month
	
	year = str(today.year)
	year = "0"*(4-len(year)) + year
	return f"{day}.{month}.{year}"