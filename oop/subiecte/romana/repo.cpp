#include "./repo.hpp"

#include <fstream>
#include <cassert>
#include <iostream>

void RepoGame::readAllFromFile() {
	std::ifstream fin(m_filePath);
	std::string line;
	while (getline(fin, line)) {
		std::vector<std::string> fields;
		std::string field = "";
		for (size_t i = 0; i < line.size(); ++i) {
			if (line[i] == ' ') {
				fields.push_back(field);
				field.clear();
			} else {
				field += line[i];
			}
		}
		fields.push_back(field);
		
		if (fields.size() >= 5) {
			int id = std::stoi(fields[0]);
			int dim = std::stoi(fields[1]);
			std::string board = fields[2];
			char next = fields[3][0];
			GameState state = GameState::NEINCEPUT;
			std::string stateString = fields[4];
			if (stateString == "NEINCEPUT") {
				state = GameState::NEINCEPUT;
			} else if (stateString == "IN_DERULARE") {
				state = GameState::IN_DERULARE;
			} else if (stateString == "TERMINAT") {
				state = GameState::TERMINAT;
			}
			
			Game game { id, dim, board, next, state };
			m_games.push_back(game);
		}
	}
}

void RepoGame::writeAllToFile() const {
	std::ofstream fout(m_filePath);
	for (const auto &game : m_games) {
		fout       << game.getId()
			<< " " << game.getDim()
			<< " " << game.getBoard()
			<< " " << game.getNext()
			<< " " << gameStateToString(game.getState())
			<< "\n";
		;
	}
}

RepoGame::RepoGame(const std::string &filePath)
: m_filePath(filePath)
{
	readAllFromFile();
}

const std::vector<Game> &RepoGame::getAll() const {
	return m_games;
}

void RepoGame::store(const Game &game) {
	for (const auto &storedGame : m_games) {
		if (storedGame.getId() == game.getId()) {
			return;
		}
	}
	m_games.push_back(game);
	writeAllToFile();
}

void RepoGame::update(const Game &game) {
	for (auto &storedGame : m_games) {
		if (storedGame.getId() == game.getId()) {
			storedGame = game;
			writeAllToFile();
			return;
		}
	}
	return;
}

Game RepoGame::find(int id) const {
	for (const auto &storedGame : m_games) {
		if (storedGame.getId() == id) {
			return storedGame;
		}
	}
}

int RepoGame::getNextId() const {
	int id = 0;
	for (const auto &game : m_games) {
		if (game.getId() >= id) {
			id = game.getId()+1;
		}
	}
	return id;
}

void testRepo() {
	std::ofstream fout {"./games_test.txt"};
		fout << "0 3 X-OXO-XOO X TERMINAT\n";
		fout << "1 4 -X-X---XO--O-O-- X IN_DERULARE\n";
		fout << "2 5 ------------------------- X NEINCEPUT\n";
	fout.close();
	
	RepoGame repo {"./games_test.txt"};
	auto games = repo.getAll();
	
	assert(games[0] == Game(0, 3, "X-OXO-XOO", 'X', GameState::TERMINAT));
	assert(games[1] == Game(1, 4, "-X-X---XO--O-O--", 'X', GameState::IN_DERULARE));
	assert(games[2] == Game(2, 5, "-------------------------", 'X', GameState::NEINCEPUT));
	
	Game game1 = Game(3, 3, "----X----", 'O', GameState::IN_DERULARE);
	repo.store(game1);
	assert(repo.find(3) == game1);
	
	Game game2 = Game(3, 3, "----X--O-", 'X', GameState::IN_DERULARE);
	repo.update(game2);
	assert(repo.find(3) == game2);
}
