#include "./srv.hpp"

#include <algorithm>
#include <fstream>
#include <cassert>
#include <stdexcept>

void SrvGame::publish() {
	for (const auto &callbackAndId : m_callbacks) {
		callbackAndId.second();
	}
}

SrvGame::SrvGame(RepoGame &repo)
: m_repo(repo)
{ }

const std::vector<Game> &SrvGame::getGames() const {
	return m_repo.getAll();
}

std::vector<Game> SrvGame::getGamesSortedByState() const {
	auto games = m_repo.getAll();
	std::sort(
		games.begin(), games.end(),
		[](const Game &lhs, const Game &rhs) { return lhs.getState() < rhs.getState(); }
	);
	return games;
}

void SrvGame::addGame(
	int dim, 
	const std::string &board, 
	char next
) {
	if (dim != 3 && dim != 4 && dim != 5) {
		throw std::runtime_error {"dimensiuni invalide"};
	}
	if (dim*dim != board.size()) {
		throw std::runtime_error {"dimensiunile tablei invalide"};
	}
	for (auto c : board) {
		if (c != '-' && c != 'X' && c != 'O') {
			throw std::runtime_error {"tabla invalida"};
		}
	}
	if (next != 'X' && next != 'O') {
		throw std::runtime_error {"jucator invalid"};
	}
	
	m_repo.store(Game(
		m_repo.getNextId(),
		dim,
		board,
		next,
		GameState::NEINCEPUT
	));
	publish();
}

void SrvGame::updateGame(
	int id,
	int dim, 
	const std::string &board, 
	char next,
	GameState state
) {
	if (dim != 3 && dim != 4 && dim != 5) {
		throw std::runtime_error {"dimensiuni invalide"};
	}
	if (dim*dim != board.size()) {
		throw std::runtime_error {"dimensiunile tablei invalide"};
	}
	for (auto c : board) {
		if (c != '-' && c != 'X' && c != 'O') {
			throw std::runtime_error {"tabla invalida"};
		}
	}
	if (next != 'X' && next != 'O') {
		throw std::runtime_error {"jucator invalid"};
	}
	
	m_repo.update(Game(
		id,
		dim,
		board,
		next,
		state
	));
	publish();
}

Game SrvGame::getGame(
	int id
) {
	return m_repo.find(id);
}

void SrvGame::makeMove(
	int id,
	int row, int column
) {
	Game game = m_repo.find(id);
	int dim = game.getDim();
	if (row < 0 || row >= dim || column < 0 || column >= dim) {
		return;
	}
	
	int index = row*dim + column;
	std::string board = game.getBoard();
	if (board[index] != '-') {
		return;
	}
	
	board[index] = game.getNext();
	game.setBoard(board);
	if (game.getNext() == 'X') {
		game.setNext('O');
	} else if (game.getNext() == 'O') {
		game.setNext('X');
	}
	
	m_repo.update(game);
	publish();
}

int SrvGame::subscribeToUpdate(
	std::function<void()> callback
) {
	int callbackId = m_nextCallbackId;
	m_nextCallbackId++;
	
	m_callbacks[callbackId] = callback;
	
	return callbackId;
}

void SrvGame::unsubscribeFromUpdate(
	int callbackId
) {
	m_callbacks.erase(callbackId);
}

void testSrv() {
	std::ofstream fout {"./games_test.txt"};
		fout << "0 3 X-OXO-XOO X TERMINAT\n";
		fout << "1 4 -X-X---XO--O-O-- X IN_DERULARE\n";
		fout << "2 5 ------------------------- X NEINCEPUT\n";
	fout.close();
	
	RepoGame repo {"./games_test.txt"};
	SrvGame srv {repo};
	auto games = srv.getGames();
	
	assert(games[0] == Game(0, 3, "X-OXO-XOO", 'X', GameState::TERMINAT));
	assert(games[1] == Game(1, 4, "-X-X---XO--O-O--", 'X', GameState::IN_DERULARE));
	assert(games[2] == Game(2, 5, "-------------------------", 'X', GameState::NEINCEPUT));
	
	auto sortedGames = srv.getGamesSortedByState();
	assert(sortedGames[0] == Game(2, 5, "-------------------------", 'X', GameState::NEINCEPUT));
	assert(sortedGames[1] == Game(1, 4, "-X-X---XO--O-O--", 'X', GameState::IN_DERULARE));
	assert(sortedGames[2] == Game(0, 3, "X-OXO-XOO", 'X', GameState::TERMINAT));
	
	assert(srv.getGame(0) == Game(0, 3, "X-OXO-XOO", 'X', GameState::TERMINAT));
	assert(srv.getGame(1) == Game(1, 4, "-X-X---XO--O-O--", 'X', GameState::IN_DERULARE));
	assert(srv.getGame(2) == Game(2, 5, "-------------------------", 'X', GameState::NEINCEPUT));
	
	Game game1 = Game(3, 3, "---------", 'O', GameState::NEINCEPUT);
	srv.addGame(3, "---------", 'O');
	assert(srv.getGame(3) == game1);
	
	Game game2 = Game(3, 3, "X--------", 'X', GameState::IN_DERULARE);
	srv.updateGame(3, 3, "X--------", 'X', GameState::IN_DERULARE);
	assert(srv.getGame(3) == game2);
}
