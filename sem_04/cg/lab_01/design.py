# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.10.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1204, 941)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.x_val_input = QtWidgets.QLineEdit(self.centralwidget)
        self.x_val_input.setGeometry(QtCore.QRect(10, 10, 113, 37))
        self.x_val_input.setObjectName("x_val_input")
        self.y_val_input = QtWidgets.QLineEdit(self.centralwidget)
        self.y_val_input.setGeometry(QtCore.QRect(190, 10, 113, 37))
        self.y_val_input.setObjectName("y_val_input")
        self.add_point_btn = QtWidgets.QPushButton(self.centralwidget)
        self.add_point_btn.setGeometry(QtCore.QRect(350, 20, 105, 39))
        self.add_point_btn.setObjectName("add_point_btn")
        self.run_btn = QtWidgets.QPushButton(self.centralwidget)
        self.run_btn.setGeometry(QtCore.QRect(350, 170, 105, 39))
        self.run_btn.setObjectName("run_btn")
        self.back_button = QtWidgets.QPushButton(self.centralwidget)
        self.back_button.setGeometry(QtCore.QRect(350, 70, 105, 39))
        self.back_button.setObjectName("back_button")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(10, 60, 161, 23))
        self.label.setObjectName("label")
        self.points_table = QtWidgets.QTableWidget(self.centralwidget)
        self.points_table.setGeometry(QtCore.QRect(10, 90, 321, 831))
        self.points_table.setRowCount(0)
        self.points_table.setColumnCount(2)
        self.points_table.setObjectName("points_table")
        self.points_table.horizontalHeader().setDefaultSectionSize(150)
        self.del_btn = QtWidgets.QPushButton(self.centralwidget)
        self.del_btn.setGeometry(QtCore.QRect(350, 120, 105, 39))
        self.del_btn.setObjectName("del_btn")
        self.del_num_input = QtWidgets.QLineEdit(self.centralwidget)
        self.del_num_input.setGeometry(QtCore.QRect(470, 120, 121, 37))
        self.del_num_input.setObjectName("del_num_input")
        self.task_btn = QtWidgets.QPushButton(self.centralwidget)
        self.task_btn.setGeometry(QtCore.QRect(470, 20, 105, 39))
        self.task_btn.setObjectName("task_btn")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsView.setGeometry(QtCore.QRect(470, 170, 731, 761))
        self.graphicsView.setObjectName("graphicsView")
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.x_val_input.setText(_translate("MainWindow", "значение х"))
        self.y_val_input.setText(_translate("MainWindow", "значение у"))
        self.add_point_btn.setText(_translate("MainWindow", "Добавить"))
        self.run_btn.setText(_translate("MainWindow", "Искать"))
        self.back_button.setText(_translate("MainWindow", "Назад"))
        self.label.setText(_translate("MainWindow", "Введенные точки"))
        self.del_btn.setText(_translate("MainWindow", "Удалить"))
        self.del_num_input.setText(_translate("MainWindow", "Номер точки"))
        self.task_btn.setText(_translate("MainWindow", "Условие"))

