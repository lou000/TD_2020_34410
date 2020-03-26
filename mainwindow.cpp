#include "mainwindow.h"
#include "lab1.h"
#include "lab2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Transmisja danych - Laboratoria - by Lewicki Maciej");
    this->setFixedSize(QSize(1400, 800));
    this->setContentsMargins(10, 10, 10, 10);
    centralWidget = new QTabWidget(this);
    centralWidget->insertTab(0, new Lab1(centralWidget), "Lab1");
    centralWidget->insertTab(1, new Lab2(centralWidget), "Lab2");
    centralWidget->setCurrentIndex(centralWidget->count()-1);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}


