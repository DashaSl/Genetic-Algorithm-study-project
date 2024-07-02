import sys
from PyQt6 import QtCore
from PyQt6.QtCore import Qt, QSize
from PyQt6.QtWidgets import QApplication, QLabel, QMainWindow, QTextEdit, QPushButton, QVBoxLayout, QWidget
import pyqtgraph as pg
import math

var_for_est = 0.5

import random as rd 

def get_esteem():
    global var_for_est
    var_for_est+=0.5
    return math.log(var_for_est)

def get_three_best():
    a = [rd.randint(-15, 15) for i in range(5)]
    b = [rd.randint(-15, 15) for i in range(5)]
    c = [rd.randint(-15, 15) for i in range(5)]
    return a, b, c


def pretend_alg():#настоящий алгоритм будет возвращать трёх лучших индивидов и лучшую оценку
    a, b, c = get_three_best()
    d = get_esteem()
    return a, b, c, d
  
class EsteemGraph(pg.PlotWidget):
    def __init__(self, num_of_iter):
        super().__init__()
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
            symbolSize=15,
            symbolBrush="b")



    def update(self, val):
        self.ax += 1
        self.data.append(val)
        self.x_ax.append(self.ax)
        self.line.setData(self.x_ax, self.data)


class ThreeGraph(pg.PlotWidget):
    def __init__(self, start, fin, polynome_data):#polynome_data - массив со значениями f(x) [0] = f(start), [-1] = f(fin) => деление шкалы = fin-start/(len()-1)
        super().__init__()
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
            symbolSize=2,
            symbolBrush="b")
        self.line2 = self.plot([],
            [],
            name="second",
            pen=pen1,
            symbolSize=2,
            symbolBrush="b")
        self.line3 = self.plot([],
            [],
            name="third",
            pen=pen1,
            symbolSize=2,
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

    def calc(x):
        ans = 0
        for i in range(len(self.coeff_for_pol)):
            ans += self.coeff_for_pol[i]*x**i 
        return ans

    def __init__(self):
        super().__init__()
        self.bag = [] #храним предыдущие шаги
        self.coeff_for_pol = [1, 1, -2, 0.5]
        self.step = 1.4
        self.start = -2
        self.finish = 5
        y_data = []

        x = -2
        while x <=5:
            y_data.append(0.5*x**3 - 2*x + x - 1)
            x+=0.1

        self.num_of_iter = 20
        self.counter = 0
        #создаём кнопку старта 
        self.esteem_graph = EsteemGraph(self.num_of_iter)
        self.three_graph = ThreeGraph(self.start, self.finish, y_data)
        self.button = QPushButton("Press Me!")
        self.button.clicked.connect(self.the_button_was_clicked)

        layout = QVBoxLayout()
        layout.addWidget(self.esteem_graph, stretch = 1, alignment =  Qt.AlignmentFlag.AlignLeft)
        layout.addWidget(self.three_graph, stretch = 1, alignment =  Qt.AlignmentFlag.AlignLeft)
        layout.addWidget(self.button, alignment = Qt.AlignmentFlag.AlignRight)

        container = QWidget()
        container.setLayout(layout)

        # Устанавливаем центральный виджет Window.
        self.setCentralWidget(container)



    def the_button_was_clicked(self):
        self.counter+=1

        val1, val2, val3, est = pretend_alg()
        self.esteem_graph.update(est)
        self.three_graph.update(val1, val2, val3)

        if self.counter >= 20:
            self.button.setEnabled(False)
            self.button.setText("Iter fin.")


app = QApplication([])

window = MainWindow()
window.show()

app.exec()