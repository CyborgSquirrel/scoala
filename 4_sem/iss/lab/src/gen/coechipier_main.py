# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'coechipier-main.ui'
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
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(10, 10, 581, 381))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.pushButtonLogOut = QPushButton(self.verticalLayoutWidget)
        self.pushButtonLogOut.setObjectName(u"pushButtonLogOut")

        self.horizontalLayout.addWidget(self.pushButtonLogOut)

        self.labelNume = QLabel(self.verticalLayoutWidget)
        self.labelNume.setObjectName(u"labelNume")

        self.horizontalLayout.addWidget(self.labelNume)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.tableViewMembruEchipajEliminat = QTableView(self.verticalLayoutWidget)
        self.tableViewMembruEchipajEliminat.setObjectName(u"tableViewMembruEchipajEliminat")

        self.verticalLayout_2.addWidget(self.tableViewMembruEchipajEliminat)

        self.pushButtonInvestigheazaCorp = QPushButton(self.verticalLayoutWidget)
        self.pushButtonInvestigheazaCorp.setObjectName(u"pushButtonInvestigheazaCorp")

        self.verticalLayout_2.addWidget(self.pushButtonInvestigheazaCorp)


        self.horizontalLayout_2.addLayout(self.verticalLayout_2)

        self.verticalLayout_6 = QVBoxLayout()
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_6.addItem(self.verticalSpacer_2)

        self.pushButtonCompleteazaSarcina = QPushButton(self.verticalLayoutWidget)
        self.pushButtonCompleteazaSarcina.setObjectName(u"pushButtonCompleteazaSarcina")

        self.verticalLayout_6.addWidget(self.pushButtonCompleteazaSarcina)

        self.labelSarciniCompletate = QLabel(self.verticalLayoutWidget)
        self.labelSarciniCompletate.setObjectName(u"labelSarciniCompletate")

        self.verticalLayout_6.addWidget(self.labelSarciniCompletate)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_6.addItem(self.verticalSpacer)


        self.horizontalLayout_2.addLayout(self.verticalLayout_6)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.pushButtonLogOut.setText(QCoreApplication.translate("MainWindow", u"Log Out", None))
        self.labelNume.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.pushButtonInvestigheazaCorp.setText(QCoreApplication.translate("MainWindow", u"Investigheaz\u0103 Corp", None))
        self.pushButtonCompleteazaSarcina.setText(QCoreApplication.translate("MainWindow", u"Completeaz\u0103 Sarcin\u0103", None))
        self.labelSarciniCompletate.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
    # retranslateUi

