QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator

TEMPLATE = app

SOURCES += \
        main.cpp \
        display.cpp \
        calculator.cpp \
		keyboard.cpp

HEADERS += \
        display.h \
        calculator.h \
		keyboard.h \
		bgvalue.h

RESOURCES += \
		res.qrc
