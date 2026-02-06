#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QQmlContext>
#include <QDebug>
#include <QCompleter>
#include <QStringListModel>
#include <QFile>
#include <QDir>
#include <QLineEdit>

//Lemoel

/*
==============================
Construtor da janela principal
==============================
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::MainWindow)
{
    ui->setupUi (this);
    mainTrie = new Trie();
    meuGrafo = new Grafo();
    loader = new DataManager();

    //garante que o conteúdo qml preencha o widget
    ui->ImagemMapa->setResizeMode (QQuickWidget::SizeRootObjectToView);
    ui->ImagemMapa->setSource (QUrl (QStringLiteral ("qrc:/mapaPelotas.qml")));

    QString caminho = "C:/Users/WINDOWS 10/OneDrive/Desktop/TrabalhoFinalA-D2/ArqJSON";
    QDir diretorio(caminho);

    qDebug() << "--- DEBUG DE CAMINHO ---";
    qDebug() << "A pasta existe?" << diretorio.exists();
    qDebug() << "O arquivo edges.json existe lá dentro?" << QFile::exists(caminho + "/edges.json");
    qDebug() << "Caminho absoluto que o Qt está vendo:" << diretorio.absolutePath();
    qDebug() << "------------------------";
    loader->carregarTodosArquivos(caminho, mainTrie, meuGrafo);
    loader->carregarTodosArquivos(caminho, mainTrie, meuGrafo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
=====================
Comando do botao sair
=====================
*/

void MainWindow::on_botaoSair_clicked()
{
    QMessageBox::StandardButton  resposta = QMessageBox::question (this, "", "Deseja sair do programa?", QMessageBox::Yes | QMessageBox::No);
    if (resposta == QMessageBox::Yes) {
        close();
    }
    else{
        qDebug() << "Programa não foi fechado";
    }
}

/*
======================
Botao de calcular rota
======================
*/

void MainWindow::on_calcularRota_clicked()
{
    QString variOrigem = ui->campoOrigem->text();
    QString variDestino = ui->campoDestino->text();

    if (variOrigem == "" || variDestino == "") {
        QMessageBox::warning (this, "Erro de digitação!", "Campos não preenchidos");
        return;
    }
    else {
        qDebug() << "Origem é: " << variOrigem;
        qDebug() << "Destino é: " << variDestino;
    }
}

void MainWindow::mostrarSugestoes(QLineEdit *campo, const QString &textoRecebido)
{
    if (textoRecebido.length() < 2) {
        return;
    }

    /*
    ======================
    buscando na trie ajuda
    ======================
    */

    std::string prefixo = textoRecebido.toLower().toStdString();
    std::vector<std::string> ajudaPalavras = mainTrie->autoComplete(prefixo);

    QStringList listaParaExibir;
    for (const std::string& rua : ajudaPalavras) {
        listaParaExibir << QString::fromStdString(rua);
    }

    //cria a caixa de sugestões na tela
    QCompleter *completerar = new QCompleter(listaParaExibir, this);
    completerar->setCaseSensitivity(Qt::CaseInsensitive);
    campo->setCompleter(completerar);
}

/*
=========================================
Ajuda da trie para completar campo Origem
=========================================
*/

void MainWindow::on_campoOrigem_textEdited(const QString &arg2)
{
    mostrarSugestoes(ui->campoOrigem, arg2);
}


void MainWindow::on_campoDestino_textEdited(const QString &arg1)
{
    mostrarSugestoes(ui->campoDestino, arg1);
}

