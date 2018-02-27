TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cc datastructure.cc
HEADERS += datastructure.hh

QMAKE_CXXFLAGS+=-Wall -Wextra -pedantic -Werror

OTHER_FILES += \
    info.txt
