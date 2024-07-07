from datetime import date
from infra import get_today

class SrvEvent:
	def __init__(self, repo_event):
		''' Constructs SrvEvent.
		input: repo_event -- RepoEvent
		'''
		self.__repo_event = repo_event
	
	def get_next_event_id(self):
		''' Gets the next valid id which can be used for an event.
		output: int
		'''
		if len(self.__repo_event) == 0:
			return 0
		else:
			event_id = 0
			events = self.__repo_event.get_all()
			for event in events:
				event_id = max(event_id, event.get_event_id())
			return event_id+1
	
	def add_event(self, event):
		''' Stores the event into the repo.
		input: event -- Event
		'''
		self.__repo_event.store(event)
	
	def get_all_events_on_date_sorted_by_time(self, date):
		''' Gets all the events whose date is equal to the provided date, and sorts them by time.
		input: date -- str, formatted like dd.MM.yyyy
		output: list of Event
		'''
		events = self.__repo_event.get_all()
		events_filtered = []
		for event in events:
			if event.get_date() == date:
				events_filtered.append(event)
		events_filtered.sort(key=lambda event: event.get_time())
		return events_filtered
	
	def export_events(self, file_name, text):
		''' Exports all the events which have the provided text in their desc into the file specified by the provided file_name, sorted by date and time.
		input: file_name -- str
		       text -- str
		'''
		events = self.__repo_event.get_all()
		events_export = []
		for event in events:
			if event.get_desc().find(text) != -1:
				events_export.append(event)
		
		events_export.sort(key=lambda event: (event.get_date(), event.get_time()))
		with open(file_name, "w") as f:
			for event in events_export:
				f.write(f"{event}\n")