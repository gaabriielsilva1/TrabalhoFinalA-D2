#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QQmlContext>
#include <QCompleter>
#include <QStringListModel>
#include <QFile>
#include <QDir>
#include <QLineEdit>
#include <QQuickItem>

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
    mainGrafo = new Grafo();
    loader = new DataManager();

    //garante que o conteúdo qml preencha o widget
    ui->ImagemMapa->setResizeMode (QQuickWidget::SizeRootObjectToView);
    ui->ImagemMapa->setSource (QUrl (QStringLiteral ("qrc:/mapaPelotas.qml")));

    QString caminho = "C:/Users/WINDOWS 10/OneDrive/Desktop/TrabalhoFinalA-D2/ArqJSON";
    QDir diretorio(caminho);

    loader->carregarTodosArquivos(caminho, mainTrie, mainGrafo);
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
    QString variOrigem = ui->campoOrigem->text().trimmed().toLower();
    QString variDestino = ui->campoDestino->text().trimmed().toLower();

    if (variOrigem == "" || variDestino == "") {
        QMessageBox::warning (this, "Erro de digitação!", "Campos não preenchidos");
        return;
    }

    bool origemExiste = mainTrie->contem(variOrigem.toStdString());
    bool destinoExiste = mainTrie->contem(variDestino.toStdString());
    if (!origemExiste) {
        QMessageBox::critical(this, "Erro de Localização", "A rua de origem não foi encontrada em Pelotas.");
        qDebug() << "Falha na verificação: Origem inexistente ->" << variOrigem;
        return;
    }

    if (!destinoExiste) {
        QMessageBox::critical(this, "Erro de Localização", "A rua de destino não foi encontrada em Pelotas.");
        qDebug() << "Falha na verificação: Destino inexistente ->" << variDestino;
        return;
    }

    /*
    ================================
    chamada do Dijkstra para calculo
    ================================
    */

    // 1. Busca os IDs correspondentes aos nomes das ruas
    long long idOrigem = mainGrafo->getIdByName(variOrigem);
    long long idDestino = mainGrafo->getIdByName(variDestino);

    qDebug() << "Pesquisando Origem:" << variOrigem << " -> ID:" << idOrigem;
    qDebug() << "Pesquisando Destino:" << variDestino << " -> ID:" << idDestino;

    // 2. Chama o Dijkstra (que agora retorna o Par: Caminho e Distância)
    auto resultado = mainGrafo->dijkstra(idOrigem, idDestino);

    std::vector<long long> caminhoIds = resultado.first; // Lista de IDs do caminho
    double distanciaMetros = resultado.second;          // Distância total

    // 3. Verifica se a rota foi encontrada
    if (distanciaMetros < 0) {
        ui->imprimirDistancia->setText("Rota não encontrada.");
        QMessageBox::information(this, "Aviso", "Não existe uma conexão entre essas ruas.");
        return;
    }

    // 4. Atualiza o Label com os Quilômetros
    double distanciaKm = distanciaMetros / 1000.0;
    QString textoFinal = QString::number(distanciaKm, 'f', 2) + " km";
    ui->imprimirDistancia->setText(textoFinal);

    // 5. Prepara as coordenadas para o MAPA (QML)
    QVariantList rotaParaDesenhar;
    for (long long id : caminhoIds) {
        // Usa a função obterCoordenada que criamos no Grafo
        QGeoCoordinate coord = mainGrafo->obterCoordenada(id);
        rotaParaDesenhar.append(QVariant::fromValue(coord));
    }

    // 6. Envia a lista de coordenadas para a função 'desenharRota' no QML
    QObject *mapaRaiz = ui->ImagemMapa->rootObject();
    if (mapaRaiz) {
        QMetaObject::invokeMethod(mapaRaiz, "desenharRota", Q_ARG(QVariant, QVariant::fromValue(rotaParaDesenhar)));
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

    QCompleter *completerar = new QCompleter(listaParaExibir, this);
    completerar->setCaseSensitivity(Qt::CaseInsensitive);
    campo->setCompleter(completerar);
}

/*
===================================================
Ajuda da trie para completar campo origem e destino
===================================================
*/

void MainWindow::on_campoOrigem_textEdited(const QString &arg2)
{
    mostrarSugestoes(ui->campoOrigem, arg2);
}

void MainWindow::on_campoDestino_textEdited(const QString &arg1)
{
    mostrarSugestoes(ui->campoDestino, arg1);
}

