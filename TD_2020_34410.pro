QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    external/DarkStyle.cpp \
    external/framelesswindow/framelesswindow.cpp \
    external/framelesswindow/windowdragger.cpp \
    lab2/lab2.cpp \
    lab1/lab1.cpp \
    lab3/lab3.cpp \
    lab4/lab4.cpp \
    lab5/lab5_6.cpp \
    lab7/lab7_8_9.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    external/DarkStyle.h \
    external/framelesswindow/framelesswindow.h \
    external/framelesswindow/windowdragger.h \
    lab2/lab2.h \
    lab1/lab1.h \
    lab3/lab3.h \
    lab4/lab4.h \
    lab5/lab5_6.h \
    lab7/lab7_8_9.h \
    mainwindow.h \
    qchartview_with_zoom_and_drag.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    external/darkstyle.qrc \
    external/framelesswindow.qrc

FORMS += \
    external/framelesswindow/framelesswindow.ui

DISTFILES += \
    external/darkstyle/darkstyle.qss \
    external/darkstyle/icon_branch_closed.png \
    external/darkstyle/icon_branch_end.png \
    external/darkstyle/icon_branch_more.png \
    external/darkstyle/icon_branch_open.png \
    external/darkstyle/icon_checkbox_checked.png \
    external/darkstyle/icon_checkbox_checked_disabled.png \
    external/darkstyle/icon_checkbox_checked_pressed.png \
    external/darkstyle/icon_checkbox_indeterminate.png \
    external/darkstyle/icon_checkbox_indeterminate_disabled.png \
    external/darkstyle/icon_checkbox_indeterminate_pressed.png \
    external/darkstyle/icon_checkbox_unchecked.png \
    external/darkstyle/icon_checkbox_unchecked_disabled.png \
    external/darkstyle/icon_checkbox_unchecked_pressed.png \
    external/darkstyle/icon_close.png \
    external/darkstyle/icon_radiobutton_checked.png \
    external/darkstyle/icon_radiobutton_checked_disabled.png \
    external/darkstyle/icon_radiobutton_checked_pressed.png \
    external/darkstyle/icon_radiobutton_unchecked.png \
    external/darkstyle/icon_radiobutton_unchecked_disabled.png \
    external/darkstyle/icon_radiobutton_unchecked_pressed.png \
    external/darkstyle/icon_restore.png \
    external/darkstyle/icon_undock.png \
    external/darkstyle/icon_vline.png \
    external/images/icon_window_close.png \
    external/images/icon_window_maximize.png \
    external/images/icon_window_minimize.png \
    external/images/icon_window_restore.png
