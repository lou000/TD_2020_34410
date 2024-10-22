﻿#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "external/framelesswindow/framelesswindow.h"
#include "external/DarkStyle.h"
#include <QScreen>

//TODO: add option to enable and disable auto adjusting axes

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new DarkStyle);
    FramelessWindow framelessWindow;
    MainWindow* window = new MainWindow();
    framelessWindow.setContent(window);
    framelessWindow.setWindowTitle(window->windowTitle());
    QFont font = QFont("Calibri", 10);
    a.setFont(font);
    QScreen* mainScreen = QApplication::screens().at(0);
    int x = (mainScreen->size().width()-window->width()) / 2;
    int y = (mainScreen->size().height()-window->height()) / 2;
    framelessWindow.move(x, y);
    framelessWindow.show();
    return a.exec();
}
