#include "./srv.hpp"

#include <QApplication>
#include <QAbstractTableModel>
#include <QComboBox>
#include <QErrorMessage>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableView>

class GamesTableModel : public QAbstractTableModel {
private:
	SrvGame &m_srv;
	int m_callbackId;
public:
	GamesTableModel(SrvGame &srv)
	: m_srv(srv)
	{
		m_callbackId = m_srv.subscribeToUpdate(
			[this]() {
				this->beginResetModel();
				this->endResetModel();
			}
		);
	}
	~GamesTableModel() {
		m_srv.unsubscribeFromUpdate(m_callbackId);
	}
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		return m_srv.getGames().size();
	}
	int columnCount(const QModelIndex &parent = QModelIndex()) const override {
		return 5;
	}
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Game game = m_srv.getGamesSortedByState()[index.row()];
			int column = index.column();
			     if (column == 0) { return QVariant(game.getId()); }
			else if (column == 1) { return QVariant(game.getDim()); }
			else if (column == 2) { return QVariant(QString::fromStdString(game.getBoard())); }
			else if (column == 3) { return QVariant(QString::fromStdString(std::string{game.getNext()})); }
			else if (column == 4) { return QVariant(QString::fromStdString(gameStateToString(game.getState()))); }
		}
		return QVariant();
	}
};

void messageBoxRuntimeError(std::function<void()> f) {
	try {
		f();
	} catch (const std::runtime_error &ex) {
		auto errorMessage = new QErrorMessage;
		errorMessage->showMessage(QString(ex.what()));
	}
}

int main(int argc, char **argv) {
	testDomain();
	testRepo();
	testSrv();
	
	RepoGame repo {"./games.txt"};
	SrvGame srv {repo};
	
	QApplication app(argc, argv);
	
	auto window = new QWidget;
	auto layout = new QHBoxLayout;
	window->setLayout(layout);
	
	auto view = new QTableView;
	auto model = new GamesTableModel(srv);
	view->setModel(model);
	layout->addWidget(view);
	
	auto layoutControls = new QVBoxLayout;
		auto buttonCreareJoc = new QPushButton("creeaza joc");
		QObject::connect(
			buttonCreareJoc, &QPushButton::clicked,
			[&srv, model]() {
				auto windowCreare = new QWidget;
				
				auto layoutCreare = new QFormLayout;
					auto labelDim = new QLabel("dimensiune");
					auto editDim = new QLineEdit;
					layoutCreare->addRow(labelDim, editDim);
					
					auto labelBoard = new QLabel("tabla");
					auto editBoard = new QLineEdit;
					layoutCreare->addRow(labelBoard, editBoard);
					
					auto labelNext = new QLabel("jucator");
					auto editNext = new QLineEdit;
					layoutCreare->addRow(labelNext, editNext);
					
					auto buttonCreare = new QPushButton("creare");
					QObject::connect(
						buttonCreare, &QPushButton::clicked,
						[&srv, windowCreare, editDim, editBoard, editNext]() {
							messageBoxRuntimeError([&srv, windowCreare, editDim, editBoard, editNext]() {
								srv.addGame(
									editDim->text().toInt(),
									editBoard->text().toStdString(),
									editNext->text().toStdString()[0]
								);
								windowCreare->close();
							});
						}
					);
					layoutCreare->addWidget(buttonCreare);
				windowCreare->setLayout(layoutCreare);
				
				windowCreare->show();
			}
		);
		layoutControls->addWidget(buttonCreareJoc);
		
		auto buttonModificareJoc = new QPushButton("modificare joc");
		QObject::connect(
			buttonModificareJoc, &QPushButton::clicked,
			[&srv]() {
				auto windowModificare = new QWidget;
				
				auto layoutModificare = new QFormLayout;
					auto labelId = new QLabel("id");
					auto editId = new QLineEdit;
					layoutModificare->addRow(labelId, editId);
					
					auto labelDim = new QLabel("dimensiune");
					auto editDim = new QLineEdit;
					layoutModificare->addRow(labelDim, editDim);
					
					auto labelBoard = new QLabel("tabla");
					auto editBoard = new QLineEdit;
					layoutModificare->addRow(labelBoard, editBoard);
					
					auto labelNext = new QLabel("jucator");
					auto editNext = new QLineEdit;
					layoutModificare->addRow(labelNext, editNext);
					
					auto labelState = new QLabel("stare");
					auto comboBoxState = new QComboBox;
						comboBoxState->addItem("Neinceput");
						comboBoxState->addItem("In derulare");
						comboBoxState->addItem("Terminat");
					layoutModificare->addRow(labelState, comboBoxState);
					
					auto buttonModificare = new QPushButton("modificare");
					QObject::connect(
						buttonModificare, &QPushButton::clicked,
						[&srv, windowModificare, editId, editDim, editBoard, editNext, comboBoxState]() {
							GameState state = GameState::IN_DERULARE;
							if (comboBoxState->currentIndex() == 0) {
								state = GameState::NEINCEPUT;
							} else if (comboBoxState->currentIndex() == 1) {
								state = GameState::IN_DERULARE;
							} else if (comboBoxState->currentIndex() == 2) {
								state = GameState::TERMINAT;
							}
							
							messageBoxRuntimeError([&srv, windowModificare, editId, editDim, editBoard, editNext, state]() {
								srv.updateGame(
									editId->text().toInt(),
									editDim->text().toInt(),
									editBoard->text().toStdString(),
									editNext->text().toStdString()[0],
									state
								);
								windowModificare->close();
							});
						}
					);
					layoutModificare->addWidget(buttonModificare);
				windowModificare->setLayout(layoutModificare);
				
				windowModificare->show();
			}
		);
		layoutControls->addWidget(buttonModificareJoc);
		
		auto buttonCreeazaTablaDeJoc = new QPushButton("creeaza tabla de joc");
		QObject::connect(
			buttonCreeazaTablaDeJoc, &QPushButton::clicked,
			[&srv]() {
				auto windowCreare = new QWidget;
				
				auto layoutCreare = new QFormLayout;
					auto labelId = new QLabel("id");
					auto editId = new QLineEdit;
					layoutCreare->addRow(labelId, editId);
					
					auto buttonCreare = new QPushButton("creare");
					QObject::connect(
						buttonCreare, &QPushButton::clicked,
						[&srv, editId, windowCreare]() {
							int id = editId->text().toInt();
							
							Game game = srv.getGame(id);
							int dim = game.getDim();
							std::string board = game.getBoard();
							
							auto windowGame = new QWidget;
							auto layoutLine = new QVBoxLayout;
							for (int row = 0; row < dim; ++row) {
								auto layoutColumn = new QHBoxLayout;
								for (int column = 0; column < dim; ++column) {
									int index = row*dim + column;
									auto button = new QPushButton(QString::fromStdString(board.substr(index, 1)));
									QObject::connect(
										button, &QPushButton::clicked,
										[&srv, id, row, column]() {
											srv.makeMove(id, row, column);
										}
									);
									int callbackId = srv.subscribeToUpdate(
										[&srv, id, dim, row, column, button]() {
											int index = row*dim + column;
											Game game = srv.getGame(id);
											std::string board = game.getBoard();
											button->setText(QString::fromStdString(board.substr(index, 1)));
										}
									);
									QObject::connect(
										button, &QPushButton::destroyed,
										[&srv, callbackId]() {
											srv.unsubscribeFromUpdate(callbackId);
										}
									);
									layoutColumn->addWidget(button);
								}
								layoutLine->addLayout(layoutColumn);
							}
							windowGame->setLayout(layoutLine);
							
							windowGame->show();
							windowCreare->close();
						}
					);
					layoutCreare->addWidget(buttonCreare);
				windowCreare->setLayout(layoutCreare);
				
				windowCreare->show();
			}
		);
		layoutControls->addWidget(buttonCreeazaTablaDeJoc);
		
		layoutControls->addStretch();
	layout->addLayout(layoutControls);
	
	window->show();
	
	return app.exec();
}
