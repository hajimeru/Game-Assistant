QT += core widgets

TARGET = GameAssistant

TEMPLATE = app

CONFIG += c++11

DESTDIR = $$PWD/../../bin

UI_DIR = $$PWD/../../temp/ui

MOC_DIR = $$PWD/../../temp/moc

INCLUDEPATH = $$PWD/../../include

HEADERS = $$PWD/../../include/project_test_mainwindow.h \
          $$PWD/../../include/game_assistant_global.h \
          $$PWD/../../include/utils.h
          
SOURCES = $$PWD/../../src/project_test_mainwindow.cpp \
          $$PWD/../../src/main.cpp 
		  

FORMS = $$PWD/../../forms/project_test_mainwindow.ui

#LIBS = 




