QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bool3S.cpp \
    circuito.cpp \
    main.cpp \
    maincircuito.cpp \
    modifyporta.cpp \
    modifysaida.cpp \
    newcircuito.cpp

HEADERS += \
    bool3S.h \
    circuito.h \
    maincircuito.h \
    modifyporta.h \
    modifysaida.h \
    newcircuito.h

FORMS += \
    maincircuito.ui \
    modifyporta.ui \
    modifysaida.ui \
    newcircuito.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
