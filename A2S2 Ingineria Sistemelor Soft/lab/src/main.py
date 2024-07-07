import typing
import sqlalchemy
import sqlalchemy.orm
import sys
import PySide2.QtWidgets
import PySide2.QtCore

import gen.log_in
import gen.coechipier_main
import gen.impostor_main
import srv
import domain
import repo


controllers = []


def main():
    engine = sqlalchemy.create_engine(
        # "sqlite:///data.db",
        "sqlite://",
        echo=False,
    )
    domain.Base.metadata.create_all(engine)

    if True:
    # if False:
        with sqlalchemy.orm.Session(engine) as session:
            session.add_all([
                domain.Impostor(nume="Rosu", parola="pass1", stare=domain.StareMembruEchipaj.VIU),
                domain.Impostor(nume="Albastru", parola="pass2", stare=domain.StareMembruEchipaj.VIU),
                domain.Coechipier(nume="Galben", parola="pass3", stare=domain.StareMembruEchipaj.VIU, sarcini_completate=0),
                domain.Coechipier(nume="Verde", parola="pass4", stare=domain.StareMembruEchipaj.VIU, sarcini_completate=0),
                domain.Coechipier(nume="Portocaliu", parola="pass5", stare=domain.StareMembruEchipaj.VIU, sarcini_completate=0),
                domain.Coechipier(nume="Negru", parola="pass6", stare=domain.StareMembruEchipaj.VIU, sarcini_completate=0),
                domain.Coechipier(nume="Roz", parola="pass7", stare=domain.StareMembruEchipaj.VIU, sarcini_completate=0),
                domain.Coechipier(nume="Alb", parola="pass8", stare=domain.StareMembruEchipaj.VIU, sarcini_completate=0),
                domain.Coechipier(nume="Mov", parola="pass9", stare=domain.StareMembruEchipaj.ELIMINAT, sarcini_completate=0),
            ])
            session.commit()

    repo_membru_echipaj = repo.RepoMembruEchipaj(engine)
    repo_impostor = repo.RepoImpostor(engine)
    repo_coechipier = repo.RepoCoechpier(engine)
    
    srv_application = srv.SrvApplication(
        repo_membru_echipaj,
        repo_impostor,
        repo_coechipier,
    )
    
    app = PySide2.QtWidgets.QApplication(sys.argv)

    controller = ControllerLogIn(srv_application)
    controllers.append(controller)
    controller.show()
    app.exec_()


class ControllerLogIn(PySide2.QtWidgets.QMainWindow, gen.log_in.Ui_MainWindow):
    def __init__(self, srv_application: srv.SrvApplication):
        self.srv_application = srv_application
        super(type(self), self).__init__()
        self.setupUi(self)

        self.pushButtonLogIn.clicked.connect(self.__on_push_button_log_in_clicked)

    def __on_push_button_log_in_clicked(self):
        try:
            membru_echipaj = (
                self.srv_application.log_in(
                    self.lineEditNume.text(),
                    self.lineEditParola.text(),
                )
            )
        except srv.SrvException as ex:
            message_box = PySide2.QtWidgets.QMessageBox()
            message_box.setIcon(PySide2.QtWidgets.QMessageBox.Critical)
            message_box.setText(ex.to_string())
            message_box.exec_()
            return

        if isinstance(membru_echipaj, domain.Impostor):
            controller = ControllerImpostorMain(self.srv_application, membru_echipaj)
            controllers.append(controller)
            controller.show()
            return

        if isinstance(membru_echipaj, domain.Coechipier):
            controller = ControllerCoechipierMain(self.srv_application, membru_echipaj)
            controllers.append(controller)
            controller.show()
            return


class ControllerCoechipierMain(PySide2.QtWidgets.QMainWindow, gen.coechipier_main.Ui_MainWindow):
    def __init__(self, srv_application: srv.SrvApplication, coechipier: domain.Coechipier):
        self.srv_application = srv_application
        super(type(self), self).__init__()
        self.setupUi(self)

        self.coechipier = coechipier

        self.labelNume.setText(self.coechipier.nume)

        self.pushButtonLogOut.clicked.connect(self.__on_push_button_log_out_clicked)
        self.pushButtonInvestigheazaCorp.clicked.connect(self.__on_push_button_investigheaza_corp_clicked)
        self.tableViewMembruEchipajEliminat.setModel(
            ModelMembriEchipajEliminati(
                self.srv_application,
            )
        )

        self.pushButtonCompleteazaSarcina.clicked.connect(self.__on_push_button_completeaza_sarcina_clicked)
        self.srv_application.register_on_membri_echipaj_sarcini_completate_modified(self.__update_sarcini_completate)
        self.__update_sarcini_completate()

    def __update_sarcini_completate(self):
        sarcini_completate = self.srv_application.get_sarcini_completate(self.coechipier.id)
        sarcini_completate = str(sarcini_completate)
        self.labelSarciniCompletate.setText(sarcini_completate)
    
    def __on_push_button_completeaza_sarcina_clicked(self):
        self.srv_application.completeaza_sarcina(self.coechipier.id)
    
    def __on_push_button_log_out_clicked(self):
        self.close()

    def __on_push_button_investigheaza_corp_clicked(self):
        selection_model: PySide2.QtCore.QItemSelectionModel = self.tableViewMembruEchipajEliminat.selectionModel()
        selected_rows = selection_model.selectedRows()
        if len(selected_rows) <= 0:
            return

        selected_row_index: PySide2.QtCore.QModelIndex = selected_rows[0]
        selected_row_index = selected_row_index.row()
        model: ModelMembriEchipajEliminati = self.tableViewMembruEchipajEliminat.model()
        membru_echipaj: domain.MembruEchipaj = model.innerData(selected_row_index)

        try:
            self.srv_application.investigheaza_corp(self.coechipier.id, membru_echipaj.id)
        except srv.SrvException as ex:
            message_box = PySide2.QtWidgets.QMessageBox()
            message_box.setIcon(PySide2.QtWidgets.QMessageBox.Critical)
            message_box.setText(ex.to_string())
            message_box.exec_()


class ControllerImpostorMain(PySide2.QtWidgets.QMainWindow, gen.impostor_main.Ui_MainWindow):
    def __init__(self, srv_application: srv.SrvApplication, impostor: domain.Impostor):
        self.srv_application = srv_application
        super(type(self), self).__init__()
        self.setupUi(self)

        self.impostor = impostor

        self.labelNume.setText(self.impostor.nume)

        self.pushButtonLogOut.clicked.connect(self.__on_push_button_log_out_clicked)
        self.pushButtonEliminaMembru.clicked.connect(self.__on_push_button_elimina_membru_clicked)
        self.pushButtonInvestigheazaCorp.clicked.connect(self.__on_push_button_investigheaza_corp_clicked)
        self.tableViewMembruEchipajViu.setModel(
            ModelMembriEchipajVii(
                self.srv_application,
            )
        )
        self.tableViewMembruEchipajEliminat.setModel(
            ModelMembriEchipajEliminati(
                self.srv_application,
            )
        )

    def __on_push_button_log_out_clicked(self):
        self.close()

    def __on_push_button_elimina_membru_clicked(self):
        selection_model: PySide2.QtCore.QItemSelectionModel = self.tableViewMembruEchipajViu.selectionModel()
        selected_rows = selection_model.selectedRows()
        if len(selected_rows) <= 0:
            return

        selected_row_index: PySide2.QtCore.QModelIndex = selected_rows[0]
        selected_row_index = selected_row_index.row()
        model: ModelMembriEchipajVii = self.tableViewMembruEchipajViu.model()
        membru_echipaj: domain.MembruEchipaj = model.innerData(selected_row_index)

        try:
            self.srv_application.elimina_membru(self.impostor.id, membru_echipaj.id)
        except srv.SrvException as ex:
            message_box = PySide2.QtWidgets.QMessageBox()
            message_box.setIcon(PySide2.QtWidgets.QMessageBox.Critical)
            message_box.setText(ex.to_string())
            message_box.exec_()

    def __on_push_button_investigheaza_corp_clicked(self):
        selection_model: PySide2.QtCore.QItemSelectionModel = self.tableViewMembruEchipajEliminat.selectionModel()
        selected_rows = selection_model.selectedRows()
        if len(selected_rows) <= 0:
            return

        selected_row_index: PySide2.QtCore.QModelIndex = selected_rows[0]
        selected_row_index = selected_row_index.row()
        model: ModelMembriEchipajEliminati = self.tableViewMembruEchipajEliminat.model()
        membru_echipaj: domain.MembruEchipaj = model.innerData(selected_row_index)

        try:
            self.srv_application.investigheaza_corp(self.impostor.id, membru_echipaj.id)
        except srv.SrvException as ex:
            message_box = PySide2.QtWidgets.QMessageBox()
            message_box.setIcon(PySide2.QtWidgets.QMessageBox.Critical)
            message_box.setText(ex.to_string())
            message_box.exec_()


class ModelMembriEchipajVii(PySide2.QtCore.QAbstractTableModel):
    def __init__(
        self,
        srv_application: srv.SrvApplication,
        parent=None,
    ):
        super().__init__(parent)
        self.__srv_application = srv_application
        self.__headers = ["Nume"]
        self.__update()
        self.__srv_application.register_on_membri_echipaj_stare_modified(self.__update)

    def __update(self):
        self.beginResetModel()
        self.__data = self.__srv_application.get_membri_echipaj_vii()
        self.endResetModel()
    
    def innerData(self, row_index: int) -> typing.Any:
        return self.__data[row_index]
    
    def rowCount(self, parent=PySide2.QtCore.QModelIndex()):
        return len(self.__data)

    def columnCount(self, parent=PySide2.QtCore.QModelIndex()):
        return len(self.__headers)

    def data(self, index, role=PySide2.QtCore.Qt.DisplayRole):
        if not index.isValid():
            return None
        row_index = index.row()
        col_index = index.column()
        if role == PySide2.QtCore.Qt.DisplayRole:
            row = self.__data[row_index]
            if col_index == 0:
                return row.nume
        return None

    def headerData(self, section, orientation, role=PySide2.QtCore.Qt.DisplayRole):
        if role != PySide2.QtCore.Qt.DisplayRole:
            return None
        if orientation == PySide2.QtCore.Qt.Horizontal:
            return str(self.__headers[section])
        if orientation == PySide2.QtCore.Qt.Vertical:
            return str(section + 1)
        return None


class ModelMembriEchipajEliminati(PySide2.QtCore.QAbstractTableModel):
    def __init__(
        self,
        srv_application: srv.SrvApplication,
        parent=None,
    ):
        super().__init__(parent)
        self.__srv_application = srv_application
        self.__headers = ["Nume"]
        self.__update()
        self.__srv_application.register_on_membri_echipaj_stare_modified(self.__update)

    def __update(self):
        self.beginResetModel()
        self.__data = self.__srv_application.get_membri_echipaj_eliminati()
        self.endResetModel()
    
    def innerData(self, row_index: int) -> typing.Any:
        return self.__data[row_index]
    
    def rowCount(self, parent=PySide2.QtCore.QModelIndex()):
        return len(self.__data)

    def columnCount(self, parent=PySide2.QtCore.QModelIndex()):
        return len(self.__headers)

    def data(self, index, role=PySide2.QtCore.Qt.DisplayRole):
        if not index.isValid():
            return None
        row_index = index.row()
        col_index = index.column()
        if role == PySide2.QtCore.Qt.DisplayRole:
            row = self.__data[row_index]
            if col_index == 0:
                return row.nume
        return None

    def headerData(self, section, orientation, role=PySide2.QtCore.Qt.DisplayRole):
        if role != PySide2.QtCore.Qt.DisplayRole:
            return None
        if orientation == PySide2.QtCore.Qt.Horizontal:
            return str(self.__headers[section])
        if orientation == PySide2.QtCore.Qt.Vertical:
            return str(section + 1)
        return None


if __name__ == "__main__":
    main()