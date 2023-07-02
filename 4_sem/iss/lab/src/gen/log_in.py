# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'log-in.ui'
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
        MainWindow.resize(600, 399)
        MainWindow.setMaximumSize(QSize(800, 16777215))
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(220, 150, 171, 91))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.formLayout_2 = QFormLayout()
        self.formLayout_2.setObjectName(u"formLayout_2")
        self.labelNume = QLabel(self.verticalLayoutWidget)
        self.labelNume.setObjectName(u"labelNume")

        self.formLayout_2.setWidget(0, QFormLayout.LabelRole, self.labelNume)

        self.lineEditNume = QLineEdit(self.verticalLayoutWidget)
        self.lineEditNume.setObjectName(u"lineEditNume")

        self.formLayout_2.setWidget(0, QFormLayout.FieldRole, self.lineEditNume)

        self.labelParola = QLabel(self.verticalLayoutWidget)
        self.labelParola.setObjectName(u"labelParola")

        self.formLayout_2.setWidget(1, QFormLayout.LabelRole, self.labelParola)

        self.lineEditParola = QLineEdit(self.verticalLayoutWidget)
        self.lineEditParola.setObjectName(u"lineEditParola")
        self.lineEditParola.setEchoMode(QLineEdit.Password)

        self.formLayout_2.setWidget(1, QFormLayout.FieldRole, self.lineEditParola)


        self.verticalLayout.addLayout(self.formLayout_2)

        self.pushButtonLogIn = QPushButton(self.verticalLayoutWidget)
        self.pushButtonLogIn.setObjectName(u"pushButtonLogIn")

        self.verticalLayout.addWidget(self.pushButtonLogIn)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Log In", None))
        self.labelNume.setText(QCoreApplication.translate("MainWindow", u"Nume", None))
        self.labelParola.setText(QCoreApplication.translate("MainWindow", u"Parola", None))
        self.pushButtonLogIn.setText(QCoreApplication.translate("MainWindow", u"Log In", None))
    # retranslateUi

