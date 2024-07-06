from bibl2 import Algorithm


import time
import sys
from PyQt6 import QtCore
from PyQt6.QtCore import Qt, QSize
from PyQt6.QtWidgets import QApplication, QLabel, QMainWindow, QTextEdit, QPushButton, QVBoxLayout, QWidget, QLineEdit
import pyqtgraph as pg
import math

import random as rd 
  
class EsteemGraph(pg.PlotWidget):
    def __init__(self):
        super().__init__()
    def start(self, num_of_iter):
        self.data = []
        self.x_ax = []
        self.ax = 0
        self.setBackground("w")
        pen = pg.mkPen(color=(30, 30, 150), width=5) #чтобы рисовать красивые линии
        self.showGrid(x=True, y=True)
        self.setXRange(0, num_of_iter)
        self.line = self.plot(self.x_ax,
            self.data,
            name="Esteem",
            pen=pen,
            symbol="+",
            symbolSize=10,
            symbolBrush="b")



    def update(self, val):
        self.ax += 1
        self.data.append(val)
        self.x_ax.append(self.ax)
        self.line.setData(self.x_ax, self.data)


class ThreeGraph(pg.PlotWidget):
    def __init__(self):#polynome_data - массив со значениями f(x) [0] = f(start), [-1] = f(fin) => деление шкалы = fin-start/(len()-1)
        super().__init__()

    def start(self, start, fin, polynome_data):
        self.data = []
        step = (fin - start)/(len(polynome_data) - 1)
        self.x_ax = [start + step*i for i in range(0, len(polynome_data))]
        self.setBackground("w")
        pen1 = pg.mkPen(color=(255, 0, 0), width=5) #чтобы рисовать красивые линии
        pen2 = pg.mkPen(color=(0, 255, 0), width=5) #чтобы рисовать красивые линии
        pen3 = pg.mkPen(color=(0, 0, 255), width=5) #чтобы рисовать красивые линии
        self.showGrid(x=True, y=True)
        self.setXRange(start, fin)
        pen = pg.mkPen(color=(150, 120, 150), width=5) #чтобы рисовать красивые линии
        self.line = self.plot(self.x_ax,
            polynome_data,
            name="first",
            pen=pen,
            symbolSize=2,
            symbolBrush="b")


        self.line1 = self.plot([],
            [],
            name="first",
            pen=pen1,
            symbolSize=1,
            symbolBrush="b")
        self.line2 = self.plot([],
            [],
            name="second",
            pen=pen2,
            symbolSize=1,
            symbolBrush="b")
        self.line3 = self.plot([],
            [],
            name="third",
            pen=pen3,
            symbolSize=1,
            symbolBrush="b")   
    def widen_val(self, val):
        ans = []
        for i in range(len(self.x_ax)):
            tmp = (i * len(val))//len(self.x_ax)
            ans.append(val[tmp])
        return ans

    def update(self, val1, val2, val3):
        self.line1.setData(self.x_ax, self.widen_val(val1))
        self.line2.setData(self.x_ax, self.widen_val(val2))
        self.line3.setData(self.x_ax, self.widen_val(val3))

class MainWindow(QMainWindow):

    def calc(self, x):
        ans = 0
        for i in range(len(self.coeff_for_pol)):
            ans += self.coeff_for_pol[i]*x**i 
        return ans

    def __init__(self):
        super().__init__()
        #создаём кнопку старта 
        self.button = QPushButton("Press Me!")
        self.fast_button = QPushButton("Gotta go fast!")
        self.button.clicked.connect(self.the_button_was_clicked)
        self.fast_button.clicked.connect(self.go_on_without_stop)
        self.button.setEnabled(False)
        self.fast_button.setEnabled(False)

        self.button_start = QPushButton("Press when finished input")
        self.button_start.clicked.connect(self.starter)
        self.alg = None

        self.line_for_coeff = QLineEdit()
        self.line_for_coeff.setPlaceholderText("коэффициенты многочлена")
        self.line_for_start = QLineEdit()
        self.line_for_start.setPlaceholderText("начало интервала")
        self.line_for_finish = QLineEdit()
        self.line_for_finish.setPlaceholderText("конец интервала")
        self.line_for_num_of_steps = QLineEdit()
        self.line_for_num_of_steps.setPlaceholderText("количество ступеней")
        self.line_for_num_of_iter = QLineEdit()
        self.line_for_num_of_iter.setPlaceholderText("максимальное количество итераций")
        self.line_for_prob = QLineEdit()
        self.line_for_prob.setPlaceholderText("вероятность возникновения мутации")
        self.line_for_crit = QLineEdit()
        self.line_for_crit.setPlaceholderText("критерий остановки")
        self.line_for_num_of_indiv = QLineEdit()
        self.line_for_num_of_indiv.setPlaceholderText("количество особей")

        """
        self.flag_coeff = False
        self.line_for_coeff.returnPressed.connect(self.ent_coeff)
        self.flag_start = False
        self.line_for_start.returnPressed.connect(self.ent_strt)
        self.flag_finish = False
        self.line_for_finish.returnPressed.connect(self.ent_fin)
        self.flag_num_of_steps = False
        self.line_for_num_of_steps.returnPressed.connect(self.ent_step)
        self.flag_num_of_iter = False
        self.line_for_num_of_iter.returnPressed.connect(self.ent_iter)
        self.flag_num_of_indiv = False
        self.line_for_num_of_indiv.returnPressed.connect(self.ent_indiv)
        self.flag_crit = False
        self.line_for_crit.returnPressed.connect(self.ent_crt)
        self.flag_prob = False
        self.line_for_prob.returnPressed.connect(self.ent_prob)
        """

        self.coeff_for_pol = [1.0, 2.14, 3.12, 4.1324]
        self.step = 5/14
        self.start = 0
        self.finish = 5
        y_data = []
        self.num_of_iter = 200
        self.counter = 0
        self.num_of_step = 14
        self.prob = 0.1
        self.criteria = 0.001 #значения по умолчанию
        self.num_of_indiv = 8
        self.curr_best = 9999999.9
        self.alg = Algorithm(self.num_of_indiv, self.num_of_step, self.prob, self.coeff_for_pol, self.num_of_iter, self.criteria, self.start, self.finish)


        self.esteem_graph = EsteemGraph()
        self.three_graph = ThreeGraph()


        layout = QVBoxLayout()
        layout.addWidget(self.esteem_graph, stretch = 1, alignment =  Qt.AlignmentFlag.AlignLeft)
        layout.addWidget(self.three_graph, stretch = 1, alignment =  Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_coeff, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_start, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_finish, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_num_of_steps, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_num_of_indiv, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_num_of_iter, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_prob, alignment = Qt.AlignmentFlag.AlignRight)
        layout.addWidget(self.line_for_crit, alignment = Qt.AlignmentFlag.AlignRight)

        layout.addWidget(self.button, alignment = Qt.AlignmentFlag.AlignLeft)
        layout.addWidget(self.fast_button, alignment = Qt.AlignmentFlag.AlignLeft)
        layout.addWidget(self.button_start, alignment = Qt.AlignmentFlag.AlignLeft)

        container = QWidget()
        container.setLayout(layout)

        # Устанавливаем центральный виджет Window.
        self.setCentralWidget(container)

    def starter(self):
        self.coeff_for_pol = [float(i) for i in self.line_for_coeff.text().split()]
        self.num_of_step = int(self.line_for_num_of_steps.text())
        self.start = float(self.line_for_start.text())
        self.finish = float(self.line_for_finish.text())
        self.step = (self.finish - self.start)/self.num_of_step
        self.num_of_iter = int(self.line_for_num_of_iter.text())
        self.num_of_indiv = int(self.line_for_num_of_indiv.text())
        self.prob = float(self.line_for_prob.text())
        self.criteria = float(self.line_for_crit.text())
        y_data = []
        x_data = [self.start + i*(self.finish - self.start)/(self.num_of_step*25) for i in range(self.num_of_step*25)]#num_of_step*25 => (fi-st)/a = step
        for x in x_data:
            y_data.append(self.calc(x))

        print(self.coeff_for_pol)
        print(self.num_of_step)
        print(self.start, self.finish)
        print(self.step)
        print(self.num_of_iter, self.num_of_indiv)
        print(self.prob, self.criteria)


        self.esteem_graph.start(self.num_of_iter)
        self.three_graph.start(self.start, self.finish, y_data)
        self.alg = Algorithm(self.num_of_indiv, self.num_of_step, self.prob, self.coeff_for_pol, self.num_of_iter, self.criteria, self.start, self.finish)



        self.button_start.setEnabled(False)
        self.button.setEnabled(True)
        self.fast_button.setEnabled(True)


    def do_step(self):
        self.counter+=1
        if self.counter >= self.num_of_iter:
            return
        chromes, estems = self.alg.step()

        est = min(estems)
        self.curr_best = est
        self.esteem_graph.update(est)
        self.three_graph.update(chromes[0], chromes[1], chromes[2])
        if self.counter >= self.num_of_iter:
            self.button.setEnabled(False)
            self.fast_button.setEnabled(False)

    def the_button_was_clicked(self):
        self.do_step()

    def go_on_without_stop(self):
        for _ in range(self.counter, self.num_of_iter):
            self.do_step()


app = QApplication([])

window = MainWindow()
window.show()

app.exec()