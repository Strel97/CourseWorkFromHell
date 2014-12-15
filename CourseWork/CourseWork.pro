QT       += core

QT       -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    player.cpp \
    functions.cpp \
    team.cpp \
    teamcontroller.cpp \
    stadium.cpp \
    game.cpp \
    menu.cpp \
    Controller.cpp \
    DataBase.cpp \
    GameController.cpp \
    PlayerController.cpp \
    StadiumController.cpp

HEADERS += \
    player.h \
    functions.h \
    team.h \
    teamcontroller.h \
    stadium.h \
    game.h \
    menu.h \
    Controller.h \
    DataBase.h \
    GameController.h \
    PlayerController.h \
    StadiumController.h \
    RapidXml/rapidxml.hpp \
    RapidXml/rapidxml_iterators.hpp \
    RapidXml/rapidxml_print.hpp \
    RapidXml/rapidxml_utils.hpp

