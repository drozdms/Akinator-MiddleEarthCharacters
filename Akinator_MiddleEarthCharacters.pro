QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Attribute.h \
    Database.h \
    Goal.h \
    Questions.h \
    Rule.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

DEFINES += Q_COMPILER_INITIALIZER_LISTS

INCLUDEPATH +=  "C:\Program Files\boost\boost_1_75_0" \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/Aragorn.jpg \
    images/Aule.jpg \
    images/Balin.jpg \
    images/Balin.png \
    images/Balrog.jpg \
    images/Bilbo.jpg \
    images/Boromir.jpg \
    images/Denethor.jpg \
    images/Echtelion.jpg \
    images/Elrond.jpg \
    images/Eomer.jpg \
    images/Feanor.jpg \
    images/Fingolfin.jpg \
    images/Frodo.jpg \
    images/Galadriel.jpg \
    images/Gandalf.jpg \
    images/Gil-Galad.jpg \
    images/Gimli.jpg \
    images/Glorfindel.jpg \
    images/Gollum.jpg \
    images/Gondolin.jpg \
    images/Ingwe.jpg \
    images/IsAlive.jpg \
    images/Legolas.jpg \
    images/LotrIcon.png \
    images/Manwe.jpg \
    images/Melkor.jpg \
    images/Merry.jpg \
    images/Morgoth_n.jpg \
    images/Pippin.jpg \
    images/Radagast.jpg \
    images/Saruman.jpg \
    images/Sauron.jpg \
    images/Theoden.jpg \
    images/Thorin.jpg \
    images/Thranduil.jpg \
    images/Tuor.jpg \
    images/Turgon.jpg \
    images/Turin.jpg \
    images/TurinGlaurung.jpg \
    images/Ulmo.jpg \
    images/Varda.jpg \
    images/gollum_sad.jpg \
    images/middleearth.jpg \
    images/races.jpg

RESOURCES += \
    images/background.qrc
