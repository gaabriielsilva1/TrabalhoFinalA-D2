#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "grafo.h"
#include "trie.h"
#include "datamanager.h"
#include <QLineEdit>

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

    void on_calcularRota_clicked();

    void on_campoOrigem_textEdited(const QString &arg1);

    void on_campoDestino_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    // NOSSAS FERRAMENTAS PRINCIPAIS
    Trie* mainTrie;
    Grafo* mainGrafo;      // O mapa      // O corretor ortográfico
    DataManager* loader;  // O carregador de arquivos

    // FUNÇÃO AUXILIAR PARA CONFIGURAR O AUTOCOMPLETE NAS CAIXAS DE TEXTO
    void configurarAutocomplete();

    void mostrarSugestoes(QLineEdit *campo, const QString &texto);
};

#endif // MAINWINDOW_H
