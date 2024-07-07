from entity import Event

class RepoException(Exception):
	pass

class RepoEvent:
	def __init__(self, file_name):
		''' Constructs RepoEvent.
		input: file_name -- str
		'''
		self.__file_name = file_name
		self.__events = {}
		self.__read_all_from_file()
	
	def __read_all_from_file(self):
		''' Reads all the events from the file.
		'''
		try:
			with open(self.__file_name, "r") as f:
				pass
		except FileNotFoundError:
			with open(self.__file_name, "w") as f:
				f.write("")
		
		with open(self.__file_name, "r") as f:
			for line in f.readlines():
				if line[-1] == "\n":
					line = line[:-1]
				if line.strip() != "":
					line = line.split(",")
					event_id = int(line[0])
					date = line[1]
					time = line[2]
					desc = line[3]
					self.__events[event_id] = Event(event_id, date, time, desc)
	
	def __write_all_to_file(self):
		''' Writes all the events to the file.
		'''
		with open(self.__file_name, "w") as f:
			for event in self.__events.values():
				f.write(f"{event.get_event_id()},{event.get_date()},{event.get_time()},{event.get_desc()}\n")
	
	def store(self, event):
		''' Stores the provided event into the repo, and writes it into the file.
		input: event -- Event
		raises: RepoException, if the event is already in the repo
		'''
		if event.get_event_id() in self.__events:
			raise RepoException("The event with provided event_id is already in the repo")
		else:
			self.__events[event.get_event_id()] = event
		self.__write_all_to_file()
	
	def get_all(self):
		''' Gets all the events.
		output: list of Event
		'''
		return list(self.__events.values())
	
	def __len__(self):
		''' Gets the amount of events in the repo.
		output: int
		'''
		return len(self.__events)