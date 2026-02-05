#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QQmlContext>
#include <QDebug>

//Lemoel

/*
=======================
Comando do botao "sair"
=======================
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //garante que o conteúdo qml preencha o widget
    ui->ImagemMapa->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->ImagemMapa->setSource(QUrl(QStringLiteral("qrc:/mapaPelotas.qml")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
=======================
Comando do botao "sair"
=======================
*/

void MainWindow::on_botaoSair_clicked()
{
    QMessageBox::StandardButton  resposta = QMessageBox::question(this, "", "Deseja sair do programa?", QMessageBox::Yes | QMessageBox::No);
    if(resposta == QMessageBox::Yes){
        close();
    }
    else{
        qDebug() << "Programa não foi fechado";
    }
}

/*
=======================
Botao de calcular rota
=======================
*/

void MainWindow::on_calcularRota_clicked()
{
    QString variOrigem = ui->campoOrigem->text();
    QString variDestino = ui->campoDestino->text();

    if(variOrigem == "" || variDestino == ""){
        QMessageBox::warning(this, "Erro de digitação!", "Campos não preenchidos");
        return;
    }
    else {
        qDebug() << "Origem é: " << variOrigem;
        qDebug() << "Destino é: " << variDestino;
    }
}

