#include "./graphical_ui.hpp"

const size_t ID_MAX = 1000000000;

QVariant cartiData(const QModelIndex &index, int role, const Carte &carte) {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int column = index.column();
		     if (column == 0) return QVariant((int) carte.get_id());
		else if (column == 1) return QVariant(QString(carte.get_titlu().c_str()));
		else if (column == 2) return QVariant(QString(carte.get_autor().c_str()));
		else if (column == 3) return QVariant(QString(carte.get_gen().c_str()));
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

QGroupBox *GraphicalUi::boxCrud(SrvCartiModel *model) {
	SrvCarti &srv_carti = this->srv_carti;
	ReportsGen &reportsGen = this->reportsGen;
	
	QVBoxLayout *layout_crud = new QVBoxLayout;
	QGroupBox *box_crud = new QGroupBox("Edit");
	box_crud->setLayout(layout_crud);
	
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
	
	// MODIFICA CARTE
	QPushButton *button_undo = new QPushButton("&undo");
	layout_crud->addWidget(button_undo);
	
	return box_crud;
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

void showDialogReportVectorCarti(const std::vector<Carte> &carti) {
	auto dialog = new QDialog;
	dialog->setModal(true);
	
	auto layout = new QVBoxLayout;
	dialog->setLayout(layout);
	
	auto table = new QTableView;
	auto model = new VectorCartiModel(carti);
	table->setModel(model);
	table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
	layout->addWidget(table);
	
	auto button_inchide = new QPushButton("inchide");
	QObject::connect(
		button_inchide, &QPushButton::clicked,
		[dialog]() {
			dialog->close();
		}
	);
	layout->addWidget(button_inchide);
	
	dialog->exec();
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
	QWidget *page_admin = new QWidget;
	QWidget *page_cart = new QWidget;
	
	QTabWidget *tab_widget = new QTabWidget;
	tab_widget->addTab(page_admin, "admin");
	tab_widget->addTab(page_cart, "cart");
	tab_widget->show();
	
	QHBoxLayout *admin_hbox = new QHBoxLayout(page_admin);
	
	// SRV CARTI TABLE
	QTableView *table = new QTableView();
	SrvCartiModel *model = new SrvCartiModel(srv_carti);
	table->setModel(model);
	table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
	admin_hbox->addWidget(table);
	
	// ACTIONS
	QVBoxLayout *layout_actions = new QVBoxLayout;
	admin_hbox->addLayout(layout_actions);
	
	layout_actions->addWidget(this->boxCrud(model));
	layout_actions->addWidget(this->boxReports());
	
	layout_actions->addStretch();
}

int GraphicalUi::run() {
	return this->app.exec();
}
