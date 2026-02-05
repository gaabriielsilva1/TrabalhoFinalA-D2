#include "janelainiciar.h"
#include "ui_janelainiciar.h"

JanelaIniciar::JanelaIniciar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JanelaIniciar)
{
    ui->setupUi(this);
}

JanelaIniciar::~JanelaIniciar()
{
    delete ui;
}
