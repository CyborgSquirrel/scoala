class ValidatorException(Exception):
	pass

def validate_date(date):
	''' Validates a date.
	input: date -- str, must be in format dd.MM.yyyy to be valid
	output: str
	raises: ValidatorException, if the date is invalid
	'''
	exception = ValidatorException("Invalid date")
	if date[2] != '.' or date[5] != '.' or len(date) != 10:
		raise exception
	else:
		try:
			day = int(date[0:2])
		except ValueError:
			raise exception
		
		if day < 1 or day > 31:
			raise exception
		
		try:
			month = int(date[3:5])
		except ValueError:
			raise exception
		
		if month < 1 or month > 12:
			raise exception
		
		try:
			year = int(date[6:10])
		except ValueError:
			raise exception
		
		return date

def validate_time(time):
	''' Validates a time.
	input: time -- str, must be in format hh:mm to be valid
	output: str
	raises: ValidatorException, if the time is invalid
	'''
	exception = ValidatorException("Invalid time")
	if time[2] != ':' or len(time) != 5:
		raise exception
	else:
		try:
			hour = int(time[0:2])
		except ValueError:
			raise exception
		if hour < 0 or hour > 24:
			raise exception
		
		try:
			minute = int(time[3:5])
		except ValueError:
			raise exception
		if minute < 0 or minute > 60:
			raise exception
		
		return time