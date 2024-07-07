#include "./domain.hpp"

#include <cassert>

std::string gameStateToString(GameState state) {
	if (state == GameState::NEINCEPUT) {
		return "NEINCEPUT";
	} else if (state == GameState::IN_DERULARE) {
		return "IN_DERULARE";
	} else if (state == GameState::TERMINAT) {
		return "TERMINAT";
	} else {
		return "NEINCEPUT";
	}
}

Game::Game(
	int id,
	int dim,
	const std::string &board,
	char next,
	GameState state
) : m_id(id), m_dim(dim), m_board(board), m_next(next), m_state(state)
{ }

int Game::getId() const { return m_id; }
int Game::getDim() const { return m_dim; }
const std::string &Game::getBoard() const { return m_board; }
char Game::getNext() const { return m_next; }
GameState Game::getState() const { return m_state; }

void Game::setDim(int dim) { m_dim = dim; }
void Game::setBoard(const std::string &board) { m_board = board; }
void Game::setNext(char next) { m_next = next; }
void Game::setState(GameState state) { m_state = state; }

bool Game::operator==(const Game &other) {
	return m_id == other.m_id
		&& m_dim == other.m_dim
		&& m_board == other.m_board
		&& m_next == other.m_next
		&& m_state == other.m_state;
}

void testDomain() {
	Game game {0, 3, "X-OXO-XOO", 'X', GameState::TERMINAT};
	
	assert(game.getId() == 0);
	assert(game.getDim() == 3);
	assert(game.getBoard() == "X-OXO-XOO");
	assert(game.getNext() == 'X');
	assert(game.getState() == GameState::TERMINAT);
	
	Game otherGame {0, 3, "X-OXO-XOO", 'X', GameState::TERMINAT};
	assert(game == otherGame);
	
	Game yetAnotherGame {0, 3, "X-OOO-XOO", 'X', GameState::TERMINAT};
	assert(!(game == yetAnotherGame));
	
	game.setDim(4);
	game.setBoard("-X-X---XO--O-O--");
	game.setNext('X');
	game.setState(GameState::IN_DERULARE);
	
	assert(game.getDim() == 4);
	assert(game.getBoard() == "-X-X---XO--O-O--");
	assert(game.getNext() == 'X');
	assert(game.getState() == GameState::IN_DERULARE);
}
