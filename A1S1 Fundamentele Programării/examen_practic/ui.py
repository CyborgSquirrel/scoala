from entity import Event
from infra import get_today

from valid import validate_date
from valid import validate_time

class UiException(Exception):
	pass

class UiConsole:
	def __init__(self, srv_event):
		''' Constructs UiConsole.
		input: srv_event -- SrvEvent
		'''
		self.__srv_event = srv_event
		self.__next_event_id = self.__srv_event.get_next_event_id()
		self.__filter_date = get_today()
	
	def __print_filtered_events(self):
		''' Ui wrapper for SrvEvent.get_all_events_on_date_sorted_by_time .
		'''
		events = self.__srv_event.get_all_events_on_date_sorted_by_time(self.__filter_date)
		desc_underline = 6
		for event in events:
			desc_underline = max(desc_underline, len(event.get_desc())+2)
		print("------------+-------+" + "-"*desc_underline)
		print(" date       | time  | desc")
		print("------------+-------+" + "-"*desc_underline)
		for event in events:
			print(f" {event.get_date()} | {event.get_time()} | {event.get_desc()}")
		print("------------+-------+" + "-"*desc_underline)
	
	def run(self):
		''' Runs the ui.
		'''
		
		commands = {
			"add event": self.__add_event,
			"export events": self.__export_events,
			"set filter": self.__set_filter,
		}
		
		while True:
			self.__print_filtered_events()
			command = input("# ")
			try:
				method = commands[command]
			except KeyError:
				self.__error("Invalid command")
				self.__pause()
				continue
			
			try:
				method()
			except Exception as ex:
				self.__error(str(ex))
			
			self.__pause()
	
	def __pause(self):
		''' Waits for user to press enter.
		'''
		input("Press enter to continue...")
	
	def __error(self, message):
		''' Prints out an error, with the provided message.
		input: message, str
		'''
		print(f"Error: {message}")
	
	def __input(self, name, converter):
		''' Reads text from the user, and tries to convert it using provided converter.
		input: name -- str
		       converter -- function
		output: converted value
		raises: UiException, if the conversion raised an exception
		'''
		value = input(f"{name} = ")
		try:
			return converter(value)
		except:
			raise UiException(f"Invalid value for '{name}'")
	
	def __add_event(self):
		''' Ui wrapper for SrvEvent.add_event .
		'''
		date = self.__input("date", validate_date)
		time = self.__input("time", validate_time)
		desc = self.__input("desc", str)
		
		event = Event(self.__next_event_id, date, time, desc)
		self.__next_event_id += 1
		self.__srv_event.add_event(event)
		print("The event has been added successfuly!")
	
	def __export_events(self):
		''' Ui wrapper for SrvEvent.export_events .
		'''
		file_name = self.__input("file name", str)
		filter_text = self.__input("filter text", str)
		
		self.__srv_event.export_events(file_name, filter_text)
	
	def __set_filter(self):
		''' Sets __filter_date to the date the user provides.
		'''
		self.__filter_date = self.__input("filter date", validate_date)