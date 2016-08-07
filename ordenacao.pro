TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lpthread
INCLUDEPATH += /usr/lib/
CONFIG += c++11

HEADERS += \
    libs/sortview.h \
    libs/player.h

SOURCES += \
    master/sorts.cpp

OTHER_FILES += 
    README.md

