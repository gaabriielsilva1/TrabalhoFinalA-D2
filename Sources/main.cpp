#include <QApplication>
// O erro estava aqui! Você precisa voltar (..) e entrar em Headers
#include "../Headers/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
