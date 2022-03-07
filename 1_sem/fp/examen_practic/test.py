import unittest
from entity import Event
from repo import RepoException, RepoEvent
from srv import SrvEvent
from infra import get_today
from valid import ValidatorException, validate_date, validate_time

class TestEvent(unittest.TestCase):
	def test_init(self):
		event_id = 1
		date = "20.02.2021"
		time = "08:00"
		desc = "Exam FP"
		event = Event(event_id, date, time, desc)
		
		self.assertEqual(event.get_event_id(), event_id)
		self.assertEqual(event.get_date(), date)
		self.assertEqual(event.get_time(), time)
		self.assertEqual(event.get_desc(), desc)

class TestRepoEntity(unittest.TestCase):
	def setUp(self):
		file_name = "test_repo_event.txt"
		with open(file_name, "w") as f:
			f.write("")
	
	def test_init(self):
		file_name = "test_repo_event.txt"
		with open(file_name, "w") as f:
			f.write("\n  \n1,11.11.2020,12:00,Chef\n\n")
		repo_event = RepoEvent(file_name)
		self.assertEqual(len(repo_event), 1)
	
	def test_store(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		
		event = Event(1, "11.11.2020", "12:00", "Chef")
		repo_event.store(event)
		
		with open(file_name, "r") as f:
			self.assertEqual(f.read(), "1,11.11.2020,12:00,Chef\n")
		
		with self.assertRaises(RepoException) as ex:
			repo_event.store(event)
		self.assertEqual(str(ex.exception), "The event with provided event_id is already in the repo")
	
	def test_get_all(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		
		event1 = Event(1, "11.11.2020", "12:00", "Chef")
		event2 = Event(2, "20.02.2021", "08:00", "Exam FP")
		event3 = Event(3, "12.07.2018", "05:00", "Wake up")
		repo_event.store(event1)
		repo_event.store(event2)
		repo_event.store(event3)
		
		self.assertEqual(repo_event.get_all(), [event1, event2, event3])
	
	def test_len(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		
		event1 = Event(1, "11.11.2020", "12:00", "Chef")
		event2 = Event(2, "17.01.2021", "08:00", "Exam FP")
		repo_event.store(event1)
		repo_event.store(event2)
		
		self.assertEqual(len(repo_event), 2)

class TestSrvEntity(unittest.TestCase):
	def setUp(self):
		file_name = "test_repo_event.txt"
		with open(file_name, "w") as f:
			f.write("")
	
	def test_init(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		srv_event = SrvEvent(repo_event)
	
	def test_get_next_event_id(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		srv_event = SrvEvent(repo_event)
		
		self.assertEqual(srv_event.get_next_event_id(), 0)
		
		srv_event.add_event(Event(2, "17.01.2021", "10:00", "Exam FP"))
		
		self.assertEqual(srv_event.get_next_event_id(), 3)
	
	def test_add_event(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		srv_event = SrvEvent(repo_event)
		
		event = Event(1, "12.07.2008", "12:00", "Crisis")
		
		srv_event.add_event(event)
		self.assertEqual(repo_event.get_all(), [event])
	
	def test_get_all_events_on_date_sorted_by_time(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		srv_event = SrvEvent(repo_event)
		
		date = "12.01.2022"
		
		event1 = Event(1, date, "22:22", "Party")
		event2 = Event(2, date, "12:00", "Happy")
		event3 = Event(3, "12.03.1990", "23:15", "Sad")
		srv_event.add_event(event1)
		srv_event.add_event(event2)
		srv_event.add_event(event3)
		
		self.assertEqual(srv_event.get_all_events_on_date_sorted_by_time(date), [event2, event1])
	
	def test_export_events(self):
		file_name = "test_repo_event.txt"
		repo_event = RepoEvent(file_name)
		srv_event = SrvEvent(repo_event)
		
		event1 = Event(1, "17.02.2001", "22:22", "Party hard")
		event2 = Event(2, "17.02.2001", "12:00", "Study hard")
		event3 = Event(3, "12.03.1990", "23:15", "Sad")
		event4 = Event(4, "17.02.2005", "17:55", "Work hard")
		
		srv_event.add_event(event1)
		srv_event.add_event(event2)
		srv_event.add_event(event3)
		srv_event.add_event(event4)
		
		file_name_export = "test_export_events.txt"
		srv_event.export_events(file_name_export, "hard")
		
		with open(file_name_export, "r") as f:
			self.assertEqual(f.read(), "17.02.2001 12:00 Study hard\n17.02.2001 22:22 Party hard\n17.02.2005 17:55 Work hard\n")

class TestInfra(unittest.TestCase):
	def test_get_today(self):
		today = get_today()
		self.assertTrue(today[2] == '.' and today[5] == '.' and len(today) == 10)
		day = int(today[0:2])
		month = int(today[3:5])
		year = int(today[6:10])

class TestValid(unittest.TestCase):
	def test_validate_date(self):
		self.assertEqual("17.01.2022", validate_date("17.01.2022"))
		self.assertEqual("12.11.2025", validate_date("12.11.2025"))
		
		with self.assertRaises(ValidatorException) as ex:
			validate_date("100.01.2022")
		self.assertEqual(str(ex.exception), "Invalid date")
		
		with self.assertRaises(ValidatorException) as ex:
			validate_date("17.-1.2022")
		self.assertEqual(str(ex.exception), "Invalid date")
		
		with self.assertRaises(ValidatorException) as ex:
			validate_date("asaubaifad")
		self.assertEqual(str(ex.exception), "Invalid date")
	
	def test_validate_time(self):
		self.assertEqual("11:00", validate_time("11:00"))
		self.assertEqual("02:22", validate_time("02:22"))
		
		with self.assertRaises(ValidatorException) as ex:
			validate_time("-3:00")
		self.assertEqual(str(ex.exception), "Invalid time")
		
		with self.assertRaises(ValidatorException) as ex:
			validate_time("11:99")
		self.assertEqual(str(ex.exception), "Invalid time")
		
		with self.assertRaises(ValidatorException) as ex:
			validate_time("adofuabifafDUSDUSHIDHiuihu")
		self.assertEqual(str(ex.exception), "Invalid time")

unittest.main()