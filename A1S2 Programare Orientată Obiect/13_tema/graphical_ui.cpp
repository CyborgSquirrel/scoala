#include "./graphical_ui.hpp"

#include <random>

const size_t ID_MAX = 1000000000;

QVariant cartiData(const QModelIndex &index, int role, const Carte &carte) {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int column = index.column();
		     if (column == 0) return QVariant((int) carte.get_id());
		else if (column == 1) return QVariant(QString::fromStdString(carte.get_titlu()));
		else if (column == 2) return QVariant(QString::fromStdString(carte.get_autor()));
		else if (column == 3) return QVariant(QString::fromStdString(carte.get_gen()));
		else if (column == 4) return QVariant(carte.get_an());
		else return QVariant();
	} else {
		return QVariant();
	}
}

QVariant cartiHeaderData(int section, Qt::Orientation orientation, int role) {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			     if (section == 0) return QVariant("Id");
			else if (section == 1) return QVariant("Titlu");
			else if (section == 2) return QVariant("Autor");
			else if (section == 3) return QVariant("Gen");
			else if (section == 4) return QVariant("An");
			else return QVariant();
		} else if (orientation == Qt::Vertical) {
			return QVariant();
		} else {
			return QVariant();
		}
	} else {
		return QVariant();
	}
}

// SRV CARTI MODEL
SrvCartiModel::SrvCartiModel(SrvCarti &srv_carti, QObject *parent) : QAbstractTableModel(parent), srv_carti(srv_carti) { }

void SrvCartiModel::addCarte(
	const std::string &titlu,
	const std::string &autor,
	const std::string &gen,
	int an
) {
	this->beginInsertRows(QModelIndex(), this->columnCount(), this->columnCount());
	this->srv_carti.add_carte(titlu, autor, gen, an);
	this->endInsertRows();
}

void SrvCartiModel::eraseCarte(size_t id) {
	const std::vector<Carte> &carti = this->srv_carti.get_carti();
	const Carte &carte = this->srv_carti.find_carte(id);
	auto it = std::find(carti.begin(), carti.end(), carte);
	int index = it-carti.begin();
	
	this->beginRemoveRows(QModelIndex(), index, index);
	this->srv_carti.erase_carte(id);
	this->endRemoveRows();
}

void SrvCartiModel::updateCarte(
	size_t id,
	const std::string &titlu,
	const std::string &autor,
	const std::string &gen,
	int an
) {
	const std::vector<Carte> &carti = this->srv_carti.get_carti();
	const Carte &carte = this->srv_carti.find_carte(id);
	auto it = std::find(carti.begin(), carti.end(), carte);
	int index = it-carti.begin();
	
	this->srv_carti.update_carte(id, titlu, autor, gen, an);
	emit dataChanged(this->index(index, 0), this->index(index, 4));
}

void SrvCartiModel::undo() {
	this->beginResetModel();
	this->srv_carti.undo();
	this->endResetModel();
}

// QAbstractTableModel
int SrvCartiModel::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return 5;
}
int SrvCartiModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return (int) this->srv_carti.get_carti().size();
}
QVariant SrvCartiModel::data(const QModelIndex &index, int role) const {
	const Carte &carte = this->srv_carti.get_carti()[index.row()];
	return cartiData(index, role, carte);
}
QVariant SrvCartiModel::headerData(int section, Qt::Orientation orientation, int role) const {
	return cartiHeaderData(section, orientation, role);
}

// VECTOR CARTI MODEL
VectorCartiModel::VectorCartiModel(const std::vector<Carte> &carti, QObject *parent) {
	Q_UNUSED(parent);
	this->carti = carti;
}

// QAbstractTableModel
int VectorCartiModel::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return 5;
}
int VectorCartiModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return this->carti.size();
}
QVariant VectorCartiModel::data(const QModelIndex &index, int role) const {
	const Carte &carte = this->carti[index.row()];
	return cartiData(index, role, carte);
}
QVariant VectorCartiModel::headerData(int section, Qt::Orientation orientation, int role) const {
	return cartiHeaderData(section, orientation, role);
}

// CARTI PE AN MODEL
CartiPeAnModel::CartiPeAnModel(const std::map<int, int> &carti_pe_an, QObject *parent) {
	Q_UNUSED(parent);
	this->carti_pe_an = std::vector<std::pair<int, int>>();
	for (const auto &entry : carti_pe_an) {
		this->carti_pe_an.push_back(entry);
	}
}

// QAbstractTableModel
int CartiPeAnModel::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return 2;
}
int CartiPeAnModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return this->carti_pe_an.size();
}
QVariant CartiPeAnModel::data(const QModelIndex &index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int row = index.row();
		const auto &entry = this->carti_pe_an[row];
		int column = index.column();
		     if (column == 0) return QVariant((int) entry.first);
		else if (column == 1) return QVariant((int) entry.second);
		else return QVariant();
	} else {
		return QVariant();
	}
}
QVariant CartiPeAnModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			     if (section == 0) return QVariant("An");
			else if (section == 1) return QVariant("Carti");
			else return QVariant();
		} else if (orientation == Qt::Vertical) {
			return QVariant();
		} else {
			return QVariant();
		}
	} else {
		return QVariant();
	}
}

// SRV INCHIRIERI CARTE MODEL
SrvInchirieriCarteModel::SrvInchirieriCarteModel(SrvInchirieriCarte &srvInchirieriCarte, QObject *parent)
: m_srvInchirieriCarte(srvInchirieriCarte) {
	Q_UNUSED(parent);
	m_signalAddedInchiriereId = srvInchirieriCarte.connectAddedInchiriere(
		[this]() {
			this->beginResetModel();
			this->m_carti = this->m_srvInchirieriCarte.getCarti();
			this->endResetModel();
		}
	);
	m_signalEmptiedInchirieriId = srvInchirieriCarte.connectEmptiedInchirieri(
		[this]() {
			this->beginResetModel();
			this->m_carti = this->m_srvInchirieriCarte.getCarti();
			this->endResetModel();
		}
	);
}
SrvInchirieriCarteModel::~SrvInchirieriCarteModel() {
	m_srvInchirieriCarte.disconnectAddedInchiriere(m_signalAddedInchiriereId);
	m_srvInchirieriCarte.disconnectEmptiedInchirieri(m_signalEmptiedInchirieriId);
}

// QAbstractTableModel
int SrvInchirieriCarteModel::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return 5;
}
int SrvInchirieriCarteModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return m_carti.size();
}
QVariant SrvInchirieriCarteModel::data(const QModelIndex &index, int role) const {
	Carte carte = m_carti[index.row()];
	return cartiData(index, role, carte);
}
QVariant SrvInchirieriCarteModel::headerData(int section, Qt::Orientation orientation, int role) const {
	return cartiHeaderData(section, orientation, role);
}

CartGraphical::CartGraphical(SrvInchirieriCarte &srvInchirieriCarte)
	: m_srvInchirieriCarte(srvInchirieriCarte) {
	m_signalAddedInchiriereId = m_srvInchirieriCarte.connectAddedInchiriere(
		[this]() {
			m_carti = this->m_srvInchirieriCarte.getCarti();
			this->update();
		}
	);
	m_signalEmptiedInchirieriId = m_srvInchirieriCarte.connectEmptiedInchirieri(
		[this]() {
			m_carti = this->m_srvInchirieriCarte.getCarti();
			this->update();
		}
	);
}
CartGraphical::~CartGraphical() {
	m_srvInchirieriCarte.disconnectAddedInchiriere(m_signalAddedInchiriereId);
	m_srvInchirieriCarte.disconnectEmptiedInchirieri(m_signalEmptiedInchirieriId);
}
void CartGraphical::paintEvent(QPaintEvent *event) {
	QPainter painter { this };
	
	int width = this->width();
	int height = this->height();
	
	std::random_device rd;
	std::mt19937 mt(rd());
	
	std::uniform_real_distribution<float> distX(0.01, 0.99);
	std::uniform_real_distribution<float> distY(0.01, 0.99);
	
	std::uniform_int_distribution<int> distRgb(0, 256);
	std::vector<Qt::BrushStyle> patterns { Qt::Dense1Pattern, Qt::Dense2Pattern, Qt::Dense6Pattern, Qt::Dense7Pattern, Qt::HorPattern, Qt::VerPattern, Qt::CrossPattern, Qt::BDiagPattern, Qt::FDiagPattern, Qt::DiagCrossPattern };
	std::uniform_int_distribution<int> distPattern(0, patterns.size());
	
	std::uniform_int_distribution<int> distHeight(60, 100);
	std::uniform_real_distribution<float> distAspectRatio(0.5, 0.8);
	
	for (const auto &carte : m_carti) {
		size_t id = carte.get_id();
		if (m_data.count(id) == 0) {
			CartGraphicalData data;
			data.percentageX = distX(mt);
			data.percentageY = distY(mt);
			
			QColor foregroundColor { distRgb(mt), distRgb(mt), distRgb(mt) };
			QColor backgroundColor { 255-foregroundColor.red(), 255-foregroundColor.green(), 255-foregroundColor.blue() };
			Qt::BrushStyle pattern = patterns[distPattern(mt)];
			
			data.foreground = QBrush { foregroundColor, pattern };
			data.background = backgroundColor;
			
			float aspectRatio = distAspectRatio(mt);
			data.height = distHeight(mt);
			data.width = (int) ((float)data.height*aspectRatio);
			
			m_data[id] = data;
		}
		CartGraphicalData data = m_data[id];
		int coordX = (int)(data.percentageX * (float)width) - data.width/2;
		int coordY = (int)(data.percentageY * (float)height) - data.height/2;
		
		QRect rect { coordX, coordY, data.width, data.height};
		painter.fillRect(rect, data.background);
		painter.fillRect(rect, data.foreground);
		painter.drawText(rect, Qt::AlignCenter|Qt::TextWordWrap, QString::fromStdString(carte.get_titlu()));
	}
}

void handleAppException(std::function<void()> f) {
	try {
		f();
	} catch(const AppException &ex) {
		QErrorMessage *error_message = new QErrorMessage;
		error_message->showMessage(
			QString::fromStdString(ex.get_msg()),
			QString::fromStdString(ex.get_type())
		);
	}
}

QGroupBox *GraphicalUi::boxSrvCartiCrud(SrvCartiModel *model) {
	SrvCarti &srv_carti = this->srv_carti;
	ReportsGen &reportsGen = this->reportsGen;
	
	QVBoxLayout *layout_crud = new QVBoxLayout;
	QGroupBox *box = new QGroupBox("Edit");
	box->setLayout(layout_crud);
	
	// ADAUGA CARTE
	QPushButton *button_adauga_carte = new QPushButton("&adauga carte");
	QObject::connect(
		button_adauga_carte, &QPushButton::clicked,
		[model, &srv_carti, &reportsGen]() {
			QDialog *window_adauga_carte = new QDialog;
			window_adauga_carte->setWindowModality(Qt::WindowModal);
			QFormLayout *layout = new QFormLayout;
			window_adauga_carte->setLayout(layout);
			
			QLineEdit *line_edit_titlu = addField<QLineEdit>(layout, "&Titlu");
			QLineEdit *line_edit_autor = addField<QLineEdit>(layout, "A&utor");
			QLineEdit *line_edit_gen = addField<QLineEdit>(layout, "&Gen");
			QLineEdit *line_edit_an = addField<QLineEdit>(layout, "A&n");
			
			QPushButton *button_adauga = new QPushButton("adauga");
			layout->addWidget(button_adauga);
			
			QObject::connect(
				button_adauga, &QPushButton::clicked,
				[model, &srv_carti, &reportsGen, line_edit_titlu, line_edit_autor, line_edit_gen, line_edit_an, window_adauga_carte]() {
					model->addCarte(
						line_edit_titlu->text().toStdString(),
						line_edit_autor->text().toStdString(),
						line_edit_gen->text().toStdString(),
						line_edit_an->text().toInt()
					);
					reportsGen.update(srv_carti);
					window_adauga_carte->close();
				}
			);
			
			window_adauga_carte->exec();
		}
	);
	layout_crud->addWidget(button_adauga_carte);
	
	// STERGE CARTE
	QPushButton *button_sterge_carte = new QPushButton("&sterge carte");
	QObject::connect(
		button_sterge_carte, &QPushButton::clicked,
		[model, &srv_carti, &reportsGen]() {
			QDialog *window_sterge_carte = new QDialog;
			window_sterge_carte->setWindowModality(Qt::WindowModal);
			QFormLayout *layout = new QFormLayout();
			window_sterge_carte->setLayout(layout);
			
			QSpinBox *line_edit_id = addField<QSpinBox>(layout, "&Id");
			line_edit_id->setMaximum(ID_MAX);
			
			QPushButton *button_sterge = new QPushButton("sterge");
			layout->addWidget(button_sterge);
			
			QObject::connect(
				button_sterge, &QPushButton::clicked,
				[model, &srv_carti, &reportsGen, line_edit_id, window_sterge_carte]() {
					handleAppException([model, line_edit_id]() {
						model->eraseCarte(
							line_edit_id->text().toInt()
						);
					});
					reportsGen.update(srv_carti);
					window_sterge_carte->close();
				}
			);
			
			window_sterge_carte->exec();
		}
	);
	layout_crud->addWidget(button_sterge_carte);
	
	// MODIFICA CARTE
	QPushButton *button_modifica_carte = new QPushButton("&modifica carte");
	QObject::connect(
		button_modifica_carte, &QPushButton::clicked,
		[model, &srv_carti, &reportsGen]() {
			QDialog *window_modifica_carte = new QDialog;
			window_modifica_carte->setWindowModality(Qt::WindowModal);
			QFormLayout *layout = new QFormLayout();
			window_modifica_carte->setLayout(layout);
			
			QSpinBox *line_edit_id = addField<QSpinBox>(layout, "&Id");
			line_edit_id->setMaximum(ID_MAX);
			QLineEdit *line_edit_titlu = addField<QLineEdit>(layout, "&Titlu");
			QLineEdit *line_edit_autor = addField<QLineEdit>(layout, "A&utor");
			QLineEdit *line_edit_gen = addField<QLineEdit>(layout, "&Gen");
			QLineEdit *line_edit_an = addField<QLineEdit>(layout, "A&n");
			
			QPushButton *button_modifica = new QPushButton("modifica");
			layout->addWidget(button_modifica);
			
			QObject::connect(
				button_modifica, &QPushButton::clicked,
				[model, &srv_carti, &reportsGen, line_edit_id, line_edit_titlu, line_edit_autor, line_edit_gen, line_edit_an, window_modifica_carte]() {
					handleAppException([model, line_edit_id, line_edit_titlu, line_edit_autor, line_edit_gen, line_edit_an]() {
						model->updateCarte(
							line_edit_id->text().toUInt(),
							line_edit_titlu->text().toStdString(),
							line_edit_autor->text().toStdString(),
							line_edit_gen->text().toStdString(),
							line_edit_an->text().toInt()
						);
					});
					reportsGen.update(srv_carti);
					window_modifica_carte->close();
				}
			);
			
			window_modifica_carte->exec();
		}
	);
	layout_crud->addWidget(button_modifica_carte);
	
	// UNDO
	QPushButton *button_undo = new QPushButton("&undo");
	QObject::connect(
		button_undo, &QPushButton::clicked,
		[model, &srv_carti, &reportsGen]() {
			handleAppException([model]() {
				model->undo();
			});
			reportsGen.update(srv_carti);
		}
	);
	layout_crud->addWidget(button_undo);
	
	return box;
}

QGroupBox *GraphicalUi::boxSrvInchirieriCarte() {
	auto &srvInchirieriCarte = this->srv_inchirieri_carte;
	
	auto box = new QGroupBox("Actiuni");
	auto layout = new QVBoxLayout;
	box->setLayout(layout);
	
	auto buttonAddInchiriere = new QPushButton("&adauga inchiriere");
	QObject::connect(
		buttonAddInchiriere, &QPushButton::clicked,
		[&srvInchirieriCarte]() {
			auto *windowAddInchiriere = new QDialog;
			windowAddInchiriere->setWindowModality(Qt::WindowModal);
			auto *layout = new QFormLayout();
			windowAddInchiriere->setLayout(layout);
			
			auto *lineEditTitlu = addField<QLineEdit>(layout, "&Titlu");
			
			auto *buttonAdauga = new QPushButton("adauga");
			QObject::connect(
				buttonAdauga, &QPushButton::clicked,
				[&srvInchirieriCarte, windowAddInchiriere, lineEditTitlu]() {
					handleAppException([&srvInchirieriCarte, lineEditTitlu]() {
						srvInchirieriCarte.addInchiriere(lineEditTitlu->text().toStdString());
					});
					windowAddInchiriere->close();
				}
			);
			layout->addWidget(buttonAdauga);
			
			windowAddInchiriere->exec();
		}
	);
	layout->addWidget(buttonAddInchiriere);
	
	auto buttonGenereazaInchirieri = new QPushButton("g&enereaza inchirieri");
	QObject::connect(
		buttonGenereazaInchirieri, &QPushButton::clicked,
		[&srvInchirieriCarte]() {
			auto *windowGenereazaInchirieri = new QDialog;
			windowGenereazaInchirieri->setWindowModality(Qt::WindowModal);
			auto *layout = new QFormLayout();
			windowGenereazaInchirieri->setLayout(layout);
			
			auto *lineEditAmount = addField<QSpinBox>(layout, "&Numar inchirieri");
			lineEditAmount->setMaximum(1000000000);
			
			auto *buttonGenereaza = new QPushButton("genereaza");
			QObject::connect(
				buttonGenereaza, &QPushButton::clicked,
				[&srvInchirieriCarte, windowGenereazaInchirieri, lineEditAmount]() {
					srvInchirieriCarte.genereazaInchirieri(lineEditAmount->text().toInt());
					windowGenereazaInchirieri->close();
				}
			);
			layout->addWidget(buttonGenereaza);
			
			windowGenereazaInchirieri->exec();
		}
	);
	layout->addWidget(buttonGenereazaInchirieri);
	
	auto buttonEmptyInchirieri = new QPushButton("&goleste inchirieri");
	QObject::connect(
		buttonEmptyInchirieri, &QPushButton::clicked,
		[&srvInchirieriCarte]() {
			srvInchirieriCarte.emptyInchirieri();
		}
	);
	layout->addWidget(buttonEmptyInchirieri);
	
	auto buttonCsvExport = new QPushButton("&csv export");
	QObject::connect(
		buttonCsvExport, &QPushButton::clicked,
		[&srvInchirieriCarte]() {
			auto *windowCsvExport = new QDialog;
			windowCsvExport->setWindowModality(Qt::WindowModal);
			auto *layout = new QFormLayout();
			windowCsvExport->setLayout(layout);
			
			auto *lineEditFilePath = addField<QLineEdit>(layout, "Fisier");
			
			auto *buttonExport = new QPushButton("export");
			QObject::connect(
				buttonExport, &QPushButton::clicked,
				[&srvInchirieriCarte, windowCsvExport, lineEditFilePath]() {
					srvInchirieriCarte.csvExport(lineEditFilePath->text().toStdString());
					windowCsvExport->close();
				}
			);
			layout->addWidget(buttonExport);
			
			windowCsvExport->exec();
		}
	);
	layout->addWidget(buttonCsvExport);
	
	return box;
}

void configureCartiHeader(QHeaderView *horizontalHeader) {
	horizontalHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
	horizontalHeader->setSectionResizeMode(2, QHeaderView::Stretch);
	horizontalHeader->setSectionResizeMode(3, QHeaderView::Stretch);
	horizontalHeader->setSectionResizeMode(4, QHeaderView::Stretch);
}

QDialog *makeDialogReport(QAbstractTableModel *model, std::function<void(QHeaderView*)> configureHeader) {
	auto dialog = new QDialog;
	dialog->setModal(true);
	
	auto layout = new QVBoxLayout;
	dialog->setLayout(layout);
	
	auto table = new QTableView;
	table->setModel(model);
	configureHeader(table->horizontalHeader());
	layout->addWidget(table);
	
	auto button_inchide = new QPushButton("inchide");
	QObject::connect(
		button_inchide, &QPushButton::clicked,
		[dialog]() {
			dialog->close();
		}
	);
	layout->addWidget(button_inchide);
	
	return dialog;
}

QGroupBox *GraphicalUi::boxReports() {
	QVBoxLayout *layout_reports = new QVBoxLayout;
	QGroupBox *box_reports = new QGroupBox("Rapoarte");
	box_reports->setLayout(layout_reports);
	
	this->reportsGen = ReportsGen();
	this->reportsGen.update(this->srv_carti);
	auto &reportsGen = this->reportsGen;
	QPushButton *button_numar_carti_cu_gen = new QPushButton("numar carti cu gen");
	QObject::connect(
		button_numar_carti_cu_gen, &QPushButton::clicked,
		[&reportsGen]() {
			reportsGen.show();
		}
	);
	layout_reports->addWidget(button_numar_carti_cu_gen);
	
	auto &srvCarti = this->srv_carti;
	QPushButton *button_filter_by_titlu = new QPushButton("filtrat dupa titlu");
	QObject::connect(
		button_filter_by_titlu, &QPushButton::clicked,
		[&srvCarti]() {
			auto *window_filter_by_titlu = new QDialog;
			window_filter_by_titlu->setModal(true);
			
			auto *layout = new QFormLayout;
			window_filter_by_titlu->setLayout(layout);
			
			auto line_edit_filter = addField<QLineEdit>(layout, "&Filter");
			
			auto button_filtreaza = new QPushButton("filtreaza");
			QObject::connect(
				button_filtreaza, &QPushButton::clicked,
				[&srvCarti, window_filter_by_titlu, line_edit_filter]() {
					auto carti = srvCarti.filter_by_titlu(line_edit_filter->text().toStdString());
					makeDialogReport(
						new VectorCartiModel(carti),
						configureCartiHeader
					)->exec();
					window_filter_by_titlu->close();
				}
			);
			layout->addWidget(button_filtreaza);
			
			window_filter_by_titlu->exec();
		}
	);
	layout_reports->addWidget(button_filter_by_titlu);
	
	QPushButton *button_filter_by_an = new QPushButton("filtrat dupa an");
	QObject::connect(
		button_filter_by_an, &QPushButton::clicked,
		[&srvCarti]() {
			auto *window_filter_by_an = new QDialog;
			window_filter_by_an->setModal(true);
			
			auto *layout = new QFormLayout;
			window_filter_by_an->setLayout(layout);
			
			auto line_edit_an = addField<QLineEdit>(layout, "&An");
			
			auto button_filtreaza = new QPushButton("filtreaza");
			QObject::connect(
				button_filtreaza, &QPushButton::clicked,
				[&srvCarti, window_filter_by_an, line_edit_an]() {
					auto carti = srvCarti.filter_by_an(line_edit_an->text().toInt());
					makeDialogReport(
						new VectorCartiModel(carti),
						configureCartiHeader
					)->exec();
					window_filter_by_an->close();
				}
			);
			layout->addWidget(button_filtreaza);
			
			window_filter_by_an->exec();
		}
	);
	layout_reports->addWidget(button_filter_by_an);
	
	QPushButton *button_sort_by_titlu = new QPushButton("sortat dupa titlu");
	QObject::connect(
		button_sort_by_titlu, &QPushButton::clicked,
		[&srvCarti]() {
			auto carti = srvCarti.sort_by_titlu();
			makeDialogReport(
				new VectorCartiModel(carti),
				configureCartiHeader
			)->exec();
		}
	);
	layout_reports->addWidget(button_sort_by_titlu);
	
	QPushButton *button_sort_by_autor = new QPushButton("sortat dupa autor");
	QObject::connect(
		button_sort_by_autor, &QPushButton::clicked,
		[&srvCarti]() {
			auto carti = srvCarti.sort_by_autor();
			makeDialogReport(
				new VectorCartiModel(carti),
				configureCartiHeader
			)->exec();
		}
	);
	layout_reports->addWidget(button_sort_by_autor);
	
	QPushButton *button_sort_by_an_gen = new QPushButton("sortat dupa an, si gen");
	QObject::connect(
		button_sort_by_an_gen, &QPushButton::clicked,
		[&srvCarti]() {
			auto carti = srvCarti.sort_by_an_gen();
			makeDialogReport(
				new VectorCartiModel(carti),
				configureCartiHeader
			)->exec();
		}
	);
	layout_reports->addWidget(button_sort_by_an_gen);
	
	QPushButton *button_generate_report_carti_by_an = new QPushButton("numar de carti pe an");
	QObject::connect(
		button_generate_report_carti_by_an, &QPushButton::clicked,
		[&srvCarti]() {
			auto carti_pe_an = srvCarti.generate_report_carti_by_an();
			makeDialogReport(
				new CartiPeAnModel(carti_pe_an),
				[](auto horizontalHeader) {
					horizontalHeader->setSectionResizeMode(0, QHeaderView::Stretch);
					horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
				}
			)->exec();
		}
	);
	layout_reports->addWidget(button_generate_report_carti_by_an);
	
	return box_reports;
}

ReportsGen::ReportsGen() {
	this->layout = new QVBoxLayout;
}

void ReportsGen::show() {
	QWidget *window = new QWidget;
	window->setLayout(this->layout);
	window->show();
}

void ReportsGen::update(SrvCarti &srv_carti) {
	while (!this->buttons.empty()) {
		this->layout->removeWidget(this->buttons.back());
		delete this->buttons.back();
		this->buttons.pop_back();
	}
	
	auto report = srv_carti.generate_report_gen_amount();
	for (auto gen_amount : report) {
		QPushButton *button = new QPushButton(QString::fromStdString(gen_amount.first));
		int amount = gen_amount.second;
		QObject::connect(
			button, &QPushButton::clicked,
			[amount]() {
				QMessageBox *message_box = new QMessageBox;
				message_box->setText(QString::number(amount));
				message_box->show();
			}
		);
		this->layout->addWidget(button);
		this->buttons.push_back(button);
	}
}

GraphicalUi::GraphicalUi(
	int argc, char **argv,
	SrvCarti &srv_carti,
	SrvInchirieriCarte &srv_inchirieri_carte
) : app(argc, argv), srv_carti(srv_carti), srv_inchirieri_carte(srv_inchirieri_carte) {
	auto window_admin = new QWidget;
	auto window_cart = new QWidget;
	auto window_cart_graphical = new QWidget;
	
	// WINDOW ADMIN
		auto layout_admin = new QVBoxLayout(window_admin);
		
		auto label_admin = new QLabel("Admin");
		layout_admin->addWidget(label_admin);
		
		auto hbox_admin = new QHBoxLayout;
		layout_admin->addLayout(hbox_admin);
		
		// TABLE SRV CARTI
		QTableView *table_srv_carti = new QTableView();
		SrvCartiModel *model_srv_carti = new SrvCartiModel(this->srv_carti);
		table_srv_carti->setModel(model_srv_carti);
		configureCartiHeader(table_srv_carti->horizontalHeader());
		hbox_admin->addWidget(table_srv_carti);
		
		// ACTIONS
		QVBoxLayout *layout_actions = new QVBoxLayout;
		hbox_admin->addLayout(layout_actions);
		
		layout_actions->addWidget(this->boxSrvCartiCrud(model_srv_carti));
		layout_actions->addWidget(this->boxReports());
		
		layout_actions->addStretch();
	window_admin->show();
	
	// WINDOW CART
		auto layout_cart_top = new QVBoxLayout(window_cart);
		
		auto label_cart = new QLabel("Cos");
		layout_cart_top->addWidget(label_cart);
		
		QHBoxLayout *layout_cart = new QHBoxLayout;
		layout_cart_top->addLayout(layout_cart);
		
		// TABLE SRV INCHIRIERI CARTE
		QTableView *table_srv_inchirieri_carte = new QTableView;
		SrvInchirieriCarteModel *model_srv_inchirieri_carte = new SrvInchirieriCarteModel(this->srv_inchirieri_carte);
		table_srv_inchirieri_carte->setModel(model_srv_inchirieri_carte);
		configureCartiHeader(table_srv_inchirieri_carte->horizontalHeader());
		layout_cart->addWidget(table_srv_inchirieri_carte);
		
		QVBoxLayout *layout_actions_srv_inchirieri_carte = new QVBoxLayout;
		layout_cart->addLayout(layout_actions_srv_inchirieri_carte);
		
		layout_actions_srv_inchirieri_carte->addWidget(this->boxSrvInchirieriCarte());
		
		layout_actions_srv_inchirieri_carte->addStretch();
	window_cart->show();
	
	// WINDOW CART GRAPHICAL
		auto layout_cart_graphical = new QVBoxLayout(window_cart_graphical);
		
		auto cart_graphical = new CartGraphical(srv_inchirieri_carte);
		layout_cart_graphical->addWidget(cart_graphical);
	window_cart_graphical->show();
}

int GraphicalUi::run() {
	return this->app.exec();
}
