QT       += core network
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundle
INCLUDEPATH += Headers

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/datamanager.cpp \
    Sources/grafo.cpp \
    Sources/main.cpp \
    Sources/datamanager.cpp \
    Sources/trie.cpp

HEADERS += \
    Headers/datamanager.h \
    Headers/grafo.h \
    Headers/trie.h

FORMS += \
    Forms/grafo.ui

TRANSLATIONS += \
    TrabalhoFinal_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
