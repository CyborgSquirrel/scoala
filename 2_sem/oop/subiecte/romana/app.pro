CONFIG += debug
HEADERS += *.hpp
SOURCES += *.cpp
MOC_DIR = ./moc
OBJECTS_DIR = ./obj
DESTDIR = .
QMAKE_CXX = clang++
QMAKE_CXXFLAGS = -g
QT += core
QT += gui
QT += widgets
