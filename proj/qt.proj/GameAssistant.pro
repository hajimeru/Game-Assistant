QT += core widgets

TARGET = GameAssistant

TEMPLATE = app

CONFIG += c++11

DESTDIR = $$PWD/../../bin

UI_DIR = $$PWD/../../temp/ui

MOC_DIR = $$PWD/../../temp/moc

INCLUDEPATH = $$PWD/../../include \
              $$PWD/../../include/config \
              $$PWD/../../include/3rdparty \

HEADERS = $$PWD/../../include/project_test_mainwindow.h \
          $$PWD/../../include/game_assistant_global.h \
          $$PWD/../../include/utils.h \
          $$PWD/../../include/controller.h \
          $$PWD/../../include/resource.h \
          $$PWD/../../include/config/abstract_config.h \
          $$PWD/../../include/config/abstract_resource.h \
          $$PWD/../../include/config/terminal_config.h \
          
SOURCES = $$PWD/../../src/project_test_mainwindow.cpp \
          $$PWD/../../src/main.cpp \
          $$PWD/../../src/controller.cpp \
          $$PWD/../../src/resource.cpp \
          $$PWD/../../src/config/abstract_config.cpp \
          $$PWD/../../src/config/abstract_resource.cpp \
          $$PWD/../../src/config/terminal_config.cpp \
		  

FORMS = $$PWD/../../forms/project_test_mainwindow.ui

LIBS = -L$$PWD/../../lib -lopencv_world454




