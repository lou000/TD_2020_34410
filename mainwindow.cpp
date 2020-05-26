#include "mainwindow.h"
#include "lab1/lab1.h"
#include "lab2/lab2.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"
#include "lab5/lab5_6.h"
#include "lab7/lab7_8_9.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Transmisja danych - Laboratoria - by Lewicki Maciej");
    this->setFixedSize(QSize(1400, 800));
    this->setContentsMargins(10, 10, 10, 10);
    centralWidget = new QTabWidget(this);
    centralWidget->insertTab(0, new Lab1(centralWidget), "Lab1");
    centralWidget->insertTab(1, new Lab2(centralWidget), "Lab2");
    centralWidget->insertTab(2, new Lab3(centralWidget), "Lab3");
    centralWidget->insertTab(3, new Lab4(centralWidget), "Lab4");
    centralWidget->insertTab(4, new Lab5_6(centralWidget), "Lab5/6");
    centralWidget->insertTab(5, new Lab7_8_9(centralWidget), "Lab7/8/9");
    centralWidget->setCurrentIndex(centralWidget->count()-1);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}


