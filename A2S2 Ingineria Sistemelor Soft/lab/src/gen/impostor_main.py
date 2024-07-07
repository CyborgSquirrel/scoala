# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'impostor-main.ui'
##
## Created by: Qt User Interface Compiler version 5.15.9
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import *  # type: ignore
from PySide2.QtGui import *  # type: ignore
from PySide2.QtWidgets import *  # type: ignore


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(600, 400)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.centralwidget.setEnabled(True)
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(10, 10, 581, 381))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.pushButtonLogOut = QPushButton(self.verticalLayoutWidget)
        self.pushButtonLogOut.setObjectName(u"pushButtonLogOut")

        self.horizontalLayout_4.addWidget(self.pushButtonLogOut)

        self.labelNume = QLabel(self.verticalLayoutWidget)
        self.labelNume.setObjectName(u"labelNume")

        self.horizontalLayout_4.addWidget(self.labelNume)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_4.addItem(self.horizontalSpacer)


        self.verticalLayout.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.tableViewMembruEchipajEliminat = QTableView(self.verticalLayoutWidget)
        self.tableViewMembruEchipajEliminat.setObjectName(u"tableViewMembruEchipajEliminat")
        self.tableViewMembruEchipajEliminat.setSelectionMode(QAbstractItemView.SingleSelection)
        self.tableViewMembruEchipajEliminat.setSelectionBehavior(QAbstractItemView.SelectRows)

        self.verticalLayout_3.addWidget(self.tableViewMembruEchipajEliminat)

        self.pushButtonInvestigheazaCorp = QPushButton(self.verticalLayoutWidget)
        self.pushButtonInvestigheazaCorp.setObjectName(u"pushButtonInvestigheazaCorp")

        self.verticalLayout_3.addWidget(self.pushButtonInvestigheazaCorp)


        self.horizontalLayout_2.addLayout(self.verticalLayout_3)

        self.verticalLayout_5 = QVBoxLayout()
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.tableViewMembruEchipajViu = QTableView(self.verticalLayoutWidget)
        self.tableViewMembruEchipajViu.setObjectName(u"tableViewMembruEchipajViu")
        self.tableViewMembruEchipajViu.setSelectionMode(QAbstractItemView.SingleSelection)
        self.tableViewMembruEchipajViu.setSelectionBehavior(QAbstractItemView.SelectRows)

        self.verticalLayout_5.addWidget(self.tableViewMembruEchipajViu)

        self.pushButtonEliminaMembru = QPushButton(self.verticalLayoutWidget)
        self.pushButtonEliminaMembru.setObjectName(u"pushButtonEliminaMembru")

        self.verticalLayout_5.addWidget(self.pushButtonEliminaMembru)


        self.horizontalLayout_2.addLayout(self.verticalLayout_5)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"SusApp", None))
        self.pushButtonLogOut.setText(QCoreApplication.translate("MainWindow", u"Log Out", None))
        self.labelNume.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.pushButtonInvestigheazaCorp.setText(QCoreApplication.translate("MainWindow", u"Investigheaz\u0103 Corp", None))
        self.pushButtonEliminaMembru.setText(QCoreApplication.translate("MainWindow", u"Elimin\u0103 Membru", None))
    # retranslateUi

