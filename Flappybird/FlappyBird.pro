QT       += core gui multimedia
QT       +=widgets
QT      += gui
QT      += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = bitbug_favicon.ico#设置程序图标

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = bitbug_favicon.ico#设置程序图标


SOURCES += main.cpp\
    Background.cpp \
    Bird.cpp \
    GameElement.cpp \
    Ground.cpp \
    Overboard.cpp \
    Pipe.cpp \
    Readyboard.cpp \
    Scoreboard.cpp \
    Title.cpp \
    dialog.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Background.h \
    Bird.h \
    GameElement.h \
    Ground.h \
    Overboard.h \
    Pipe.h \
    Readyboard.h \
    Scoreboard.h \
    Title.h \
    dialog.h

RESOURCES += \
    resource/image.qrc \
    resource/sounds.qrc

OTHER_FILES +=

FORMS += \
    dialog.ui
