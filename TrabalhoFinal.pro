QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += .

# --- FONTES (CÓDIGO LÓGICO) ---
SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/grafo.cpp \
    Sources/trie.cpp \
    Sources/datamanager.cpp

# --- CABEÇALHOS (DECLARAÇÕES) ---
HEADERS += \
    Headers/mainwindow.h \
    Headers/grafo.h \
    Headers/trie.h \
    Headers/datamanager.h

# --- INTERFACE GRÁFICA ---
# Verifica se o mainwindow.ui está na pasta raiz junto com o .pro
# Se você moveu ele para uma pasta "Forms", mude para Forms/mainwindow.ui
FORMS += \
    Forms/mainwindow.ui

# --- IMPORTANTE: REMOVA QUALQUER LINHA QUE COMECE COM "TRANSLATIONS" ---
# Aquele erro "Failure to find .ts" acontece por causa dessa linha.
