#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "grafo.h"
#include "trie.h"
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//Lemoel

    void on_botaoSair_clicked();

    void on_pushButton_clicked();

    void on_botaoCalcular_clicked();

    void on_CalcularRota_clicked();

    void on_calcularRota_clicked();

private:
    Ui::MainWindow *ui;

    // NOSSAS FERRAMENTAS PRINCIPAIS
    Grafo* meuGrafo;      // O mapa
    Trie* minhaTrie;      // O corretor ortográfico
    DataManager* loader;  // O carregador de arquivos

    // FUNÇÃO AUXILIAR PARA CONFIGURAR O AUTOCOMPLETE NAS CAIXAS DE TEXTO
    void configurarAutocomplete();
};

#endif // MAINWINDOW_H
