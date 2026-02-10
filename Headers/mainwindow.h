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
    void on_botaoSair_clicked();

    void on_calcularRota_clicked();

    void on_campoOrigem_textEdited(const QString &arg1);

    void on_campoDestino_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Trie* mainTrie;
    Grafo* mainGrafo;
    DataManager* loader;

    //auxiliar para configurar o autocomplete nas caixas de txt
    void configurarAutocomplete();

    void mostrarSugestoes(QLineEdit *campo, const QString &texto);
};

#endif //MAINWINDOW_H
