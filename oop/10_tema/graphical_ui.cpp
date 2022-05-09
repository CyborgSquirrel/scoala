#include "./graphical_ui.hpp"

const size_t ID_MAX = 1000000000;

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
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const Carte &carte = this->srv_carti.get_carti()[index.row()];
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
QVariant SrvCartiModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

QGroupBox *GraphicalUi::boxReports() {
	QVBoxLayout *layout_reports = new QVBoxLayout;
	QGroupBox *box_reports = new QGroupBox("Rapoarte");
	box_reports->setLayout(layout_reports);
	
	this->reportsGen = ReportsGen();
	this->reportsGen.update(this->srv_carti);
	QPushButton *numar_carti_cu_gen = new QPushButton("numar carti cu gen");
	QObject::connect(
		numar_carti_cu_gen, &QPushButton::clicked,
		[this]() {
			this->reportsGen.show();
		}
	);
	layout_reports->addWidget(numar_carti_cu_gen);
	
	QPushButton *button_filter_by_titlu = new QPushButton("filtrat dupa titlu");
	layout_reports->addWidget(button_filter_by_titlu);
	QPushButton *button_filter_by_an = new QPushButton("filtrat dupa an");
	layout_reports->addWidget(button_filter_by_an);
	QPushButton *button_sort_by_titlu = new QPushButton("sortat dupa titlu");
	layout_reports->addWidget(button_sort_by_titlu);
	QPushButton *button_sort_by_autor = new QPushButton("sortat dupa autor");
	layout_reports->addWidget(button_sort_by_autor);
	QPushButton *button_sort_by_an_gen = new QPushButton("sortat dupa an, si gen");
	layout_reports->addWidget(button_sort_by_an_gen);
	QPushButton *button_generate_report_carti_by_an = new QPushButton("numar de carti pe an");
	layout_reports->addWidget(button_generate_report_carti_by_an);
	
	return box_reports;
}

ReportsGen::ReportsGen() {
	this->layout = new QVBoxLayout;
}

void ReportsGen::show() {
	QWidget *dialog = new QWidget;
	dialog->setLayout(this->layout);
	dialog->show();
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
