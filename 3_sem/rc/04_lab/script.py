import socket
import random
import string
import dataclasses


IP = "193.231.20.3"
PORT = 443


class Attempt:
	def __init__(self):
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((IP, PORT))
		self.word_len = int.from_bytes(self.s.recv(4), "big")
	
	def send_character(self, character: str):
		self.s.send(character.encode())
		response = int.from_bytes(self.s.recv(4), "big")
		if response == 0:
			return WrongLetter()
		elif response == 1:
			positions_len = int.from_bytes(self.s.recv(4), "big")
			positions = []
			for _ in range(positions_len):
				position = int.from_bytes(self.s.recv(4), "big")
				positions.append(position)
			return CorrectLetter(positions)
		elif response == 2:
			return Win()
		elif response == 3:
			return Lose()
	
	def close(self):
		self.s.close()


@dataclasses.dataclass
class Response:
	pass


@dataclasses.dataclass
class WrongLetter(Response):
	pass


@dataclasses.dataclass
class CorrectLetter(Response):
	positions: list[int]


@dataclasses.dataclass
class Lose(Response):
	pass


@dataclasses.dataclass
class Win(Response):
	pass


class WordState:
	def __init__(self, word_len):
		self.word_len = word_len
		self.characters_left = list(string.ascii_lowercase)
		random.shuffle(self.characters_left)
		self.word = [None] * word_len
		self.characters_found = 0


states = {}

words_found = set()

while len(words_found) < 3:
	print("attempt")
	
	attempt = Attempt()
	
	if attempt.word_len not in states:
		states[attempt.word_len] = WordState(attempt.word_len)
	state = states[attempt.word_len]
	
	print(state.word)
	
	while len(state.characters_left) > 0:
		character = state.characters_left[-1]
		response = attempt.send_character(character)
		
		if isinstance(response, CorrectLetter):
			for position in response.positions:
				state.word[position] = character
				state.characters_found += 1
			state.characters_left.pop()
		elif isinstance(response, WrongLetter):
			state.characters_left.pop()
		elif isinstance(response, Win):
			break
		elif isinstance(response, Lose):
			break
	
	attempt.close()
	
	if state.characters_found == state.word_len:
		word = "".join(state.word)
		words_found.add(word)

print(words_found)
