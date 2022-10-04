#include "./gui.hpp"

SrvMelodieModel::SrvMelodieModel(SrvMelodie &srv)
: m_srv(srv), m_melodii(m_srv.getMelodiiSortedByAutor())
{
	m_callbackId = m_srv.connect([this]() {
		this->beginResetModel();
		this->m_melodii = this->m_srv.getMelodiiSortedByAutor();
		this->endResetModel();
	});
}
SrvMelodieModel::~SrvMelodieModel() {
	m_srv.disconnect(m_callbackId);
}

int SrvMelodieModel::rowCount(const QModelIndex &parent) const {
	return m_srv.getLength();
}

int SrvMelodieModel::columnCount(const QModelIndex &parent) const {
	return 6;
}

QVariant SrvMelodieModel::data(const QModelIndex &index, int role) const {
	if (role == Qt::DisplayRole) {
		const Melodie &melodie = m_melodii[index.row()];
		int column = index.column();
		if (column == 0) return QVariant(melodie.getId());
		else if (column == 1) return QVariant(QString::fromStdString(melodie.getTitlu()));
		else if (column == 2) return QVariant(QString::fromStdString(melodie.getArtist()));
		else if (column == 3) return QVariant(QString::fromStdString(stringFromGen(melodie.getGen())));
		else if (column == 4) return QVariant(m_srv.getMelodiiCountWithAutor(melodie.getArtist()));
		else if (column == 5) return QVariant(m_srv.getMelodiiCountWithGen(melodie.getGen()));
	}
	return QVariant { };
}

MyWidget::MyWidget(SrvMelodie &srv) : m_srv(srv) {
	m_callbackId = m_srv.connect([this]() {
		this->update();
	});
}
MyWidget::~MyWidget() {
	m_srv.disconnect(m_callbackId);
}
float MyWidget::getRadius(int j) {
	return 10+j*2;
}
void MyWidget::paintEvent(QPaintEvent *event) {
	QPainter painter { this };
	
	float centerRadius = 5;
	
	Gen gens[] = { Gen::POP, Gen::ROCK, Gen::FOLK, Gen::DISCO };
	float margin = centerRadius;
	for (int i = 0; i < 4; ++i) {
		margin = std::max(margin, getRadius(m_srv.getMelodiiCountWithGen(gens[i])));
	}
	
	float px[] = { margin, (float) this->width() - margin, margin, (float) this->width() - margin };
	float py[] = { margin, margin, (float) this->height() - margin, (float) this->height() - margin };
	for (int i = 0; i < 4; ++i) {
		int count = m_srv.getMelodiiCountWithGen(gens[i]);
		QPointF center { px[i], py[i] };
		painter.drawEllipse(center, centerRadius, centerRadius);
		for (int j = 0; j < count; ++j) {
			float r = getRadius(j);
			painter.drawEllipse(center, r, r);
		}
	}
}

void tryCatchErrorMessage(std::function<void()> f) {
	try {
		f();
	} catch (const RepoException &ex) {
		auto errorMessage = new QErrorMessage;
		errorMessage->showMessage(QString::fromStdString(ex.getMsg()));
	}
}

MyWidget *makeGui(SrvMelodie &srv) {
	auto window = new MyWidget { srv };
	auto layout = new QHBoxLayout;
		auto model = new SrvMelodieModel(srv);
		auto view = new QTableView;
		view->setModel(model);
		view->setSelectionBehavior(QAbstractItemView::SelectRows);
		view->setSelectionMode(QAbstractItemView::SingleSelection);
		layout->addWidget(view);
		
		auto layoutControls = new QVBoxLayout;
			auto buttonAdaugaMelodie = new QPushButton("adauga melodie");
			QObject::connect(
				buttonAdaugaMelodie, &QPushButton::clicked,
				[&srv]() {
					auto windowAdauga = new QWidget;
					auto layoutAdauga = new QFormLayout;
					
					auto labelTitlu = new QLabel("Titlu");
					auto editTitlu = new QLineEdit;
					labelTitlu->setBuddy(editTitlu);
					layoutAdauga->addRow(labelTitlu, editTitlu);
					
					auto labelArtist = new QLabel("Artist");
					auto editArtist = new QLineEdit;
					labelArtist->setBuddy(editArtist);
					layoutAdauga->addRow(labelArtist, editArtist);
					
					auto labelGen = new QLabel("Gen");
					auto comboBoxGen = new QComboBox;
						comboBoxGen->addItem("pop");
						comboBoxGen->addItem("rock");
						comboBoxGen->addItem("folk");
						comboBoxGen->addItem("disco");
					labelGen->setBuddy(comboBoxGen);
					layoutAdauga->addRow(labelGen, comboBoxGen);
					
					auto buttonAdauga = new QPushButton("adauga");
					QObject::connect(
						buttonAdauga, &QPushButton::clicked,
						[&srv, windowAdauga, editTitlu, editArtist, comboBoxGen]() {
							std::string titlu = editTitlu->text().toStdString();
							std::string artist = editArtist->text().toStdString();
							int genIndex = comboBoxGen->currentIndex();
							Gen gen = Gen::POP;
							if (genIndex == 0) {
								gen = Gen::POP;
							} else if (genIndex == 1) {
								gen = Gen::ROCK;
							} else if (genIndex == 2) {
								gen = Gen::FOLK;
							} else if (genIndex == 3) {
								gen = Gen::DISCO;
							}
							
							tryCatchErrorMessage([&srv, windowAdauga, titlu, artist, gen]() {
								srv.addMelodie(
									titlu,
									artist,
									gen
								);
								windowAdauga->close();
							});
						}
					);
					layoutAdauga->addWidget(buttonAdauga);
					windowAdauga->setLayout(layoutAdauga);
					windowAdauga->show();
				}
			);
			layoutControls->addWidget(buttonAdaugaMelodie);
			
			auto buttonStergeMelodieSelectata = new QPushButton("sterge melodie selectata");
			QObject::connect(
				buttonStergeMelodieSelectata, &QPushButton::clicked,
				[&srv, view]() {
					QModelIndex index = view->selectionModel()->currentIndex();
					if (index.isValid()) {
						Melodie melodie = srv.getMelodiiSortedByAutor()[index.row()];
						int id = melodie.getId();
						tryCatchErrorMessage([&srv, id]() {
							srv.eraseMelodie(id);
						});
					}
				}
			);
			layoutControls->addWidget(buttonStergeMelodieSelectata);
			
			layoutControls->addStretch();
		layout->addLayout(layoutControls);
	window->setLayout(layout);
	
	return window;
}
