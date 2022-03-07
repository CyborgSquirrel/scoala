class Event:
	def __init__(self, event_id, date, time, desc):
		''' Constructs Event.
		input: event_id -- int
		       date -- str, must be formatted like dd.MM.yyyy
		       time -- str, must be formatted like hh:mm
		       desc -- str
		'''
		self.__event_id = event_id
		self.__date = date
		self.__time = time
		self.__desc = desc
	
	def get_event_id(self):
		''' Gets the value of event_id.
		output: event_id -- int
		'''
		return self.__event_id
	
	def get_date(self):
		''' Gets the value of date.
		output: date -- str
		'''
		return self.__date
	
	def get_time(self):
		''' Gets the value of time.
		output: time -- str
		'''
		return self.__time
	
	def get_desc(self):
		''' Gets the value of desc.
		output: desc -- str
		'''
		return self.__desc
	
	def __repr__(self):
		''' Returns the event as a printable string.
		output: str
		'''
		return f"{self.get_date()} {self.get_time()} {self.get_desc()}"