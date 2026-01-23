#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trie.h"
#include "grafo.h"
#include <QtLocation/QGeoServiceProvider>
#include <QtLocation/QGeoRoutingManager>
#include <QtPositioning/QGeoCoordinate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot para quando o usuário clicar no botão
    void on_botaoCalcular_clicked();

private:
    Ui::MainWindow *ui; // É aqui que o arquivo gerado é conectado
    Trie *trie;
    Grafo *grafo;

    void configurarMapa();
    void renderizarRota(const std::vector<long long>& idsCaminho);
    void setupAutocomplete();
};

#endif
