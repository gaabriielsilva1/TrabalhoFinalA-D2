#include "../Headers/mainwindow.h"
#include "ui_mainwindow.h" // O arquivo gerado automaticamente pelo Qt
#include <QMessageBox>     // Para janelas de aviso
#include <QCompleter>      // Para o autocomplete
#include <QCoreApplication> // Para achar onde o programa está rodando
#include <QDir>
#include <QDebug>

// --- CONSTRUTOR: A PRIMEIRA COISA QUE RODA ---
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. INICIALIZA AS CLASSES (CRIA A MEMÓRIA PARA ELAS)
    meuGrafo = new Grafo();
    minhaTrie = new Trie();
    loader = new DataManager();

    // 2. DESCOBRE ONDE ESTÃO OS ARQUIVOS JSON
    // O Qt Creator roda o executável numa pasta "build" separada.
    // Os seus arquivos JSON estão na pasta do projeto "TrabalhoFinal".

    QString pastaExecutavel = QCoreApplication::applicationDirPath();

    // TENTATIVA 1: Procurar na pasta do projeto (Geralmente 2 níveis acima do build)
    // Ajuste "TrabalhoFinal" se o nome da sua pasta for diferente!
    QString pastaDados = pastaExecutavel + "/../../TrabalhoFinal";

    // TENTATIVA 2: Se não achar lá, procura na mesma pasta do executável (Modo Release)
    if (!QFile::exists(pastaDados + "/edges.json")) {
        pastaDados = pastaExecutavel;
    }

    qDebug() << "Procurando arquivos JSON na pasta: " << pastaDados;

    // 3. CHAMA O CARREGADOR (Lê edges.json e label_to_nodes.json)
    bool sucesso = loader->carregarTodosArquivos(pastaDados, *meuGrafo, *minhaTrie);

    if (sucesso) {
        ui->statusbar->showMessage("Mapas carregados com sucesso!");

        // 4. SE CARREGOU, LIGA O AUTOCOMPLETE NAS CAIXAS DE TEXTO
        configurarAutocomplete();

    } else {
        // SE DEU ERRO, AVISA O USUÁRIO E MOSTRA O CAMINHO QUE TENTOU
        QMessageBox::critical(this, "Erro de Arquivo",
                              "Não encontrei os arquivos JSON (edges.json, etc).\n"
                              "Pasta pesquisada:\n" + pastaDados);
    }
}

// --- DESTRUTOR: LIMPEZA ---
MainWindow::~MainWindow()
{
    delete meuGrafo;
    delete minhaTrie;
    delete loader;
    delete ui;
}

// --- CONFIGURA O AUTOCOMPLETE (LISTINHA SUSPENSA) ---
void MainWindow::configurarAutocomplete() {
    // PRECISAS TER CRIADO A FUNÇÃO "getTodasRuas()" NO GRAFO.CPP/H CONFORME COMBINAMOS
    // Se ainda não criou, esta parte vai dar erro. Se der erro, comente estas linhas.

    std::vector<std::string> listaRuasStd = meuGrafo->getTodasRuas();
    QStringList listaRuasQt;

    // Converte de C++ (std::string) para Qt (QString)
    for (const std::string& rua : listaRuasStd) {
        listaRuasQt << QString::fromStdString(rua);
    }

    // Cria o motor de busca do Qt
    QCompleter *completer = new QCompleter(listaRuasQt, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive); // Ignora maiúsculas
    completer->setFilterMode(Qt::MatchContains);        // Acha pelo meio do nome

    // Conecta nos campos da tela
    ui->txtOrigem->setCompleter(completer);
    ui->txtDestino->setCompleter(completer);
}

// --- AÇÃO DO BOTÃO "CALCULAR" ---
void MainWindow::on_btnCalcular_clicked()
{
    // 1. PEGA O TEXTO DIGITADO
    QString origemTexto = ui->txtOrigem->text();
    QString destinoTexto = ui->txtDestino->text();

    if (origemTexto.isEmpty() || destinoTexto.isEmpty()) {
        QMessageBox::warning(this, "Atenção", "Preencha a origem e o destino!");
        return;
    }

    // 2. TRADUZ TEXTO -> ID (NUMERO DO NÓ)
    long long idOrigem = meuGrafo->getIdByName(origemTexto);
    long long idDestino = meuGrafo->getIdByName(destinoTexto);

    // 3. VERIFICA SE AS RUAS EXISTEM
    if (idOrigem == -1) {
        QMessageBox::warning(this, "Erro", "Rua de origem não encontrada no mapa.");
        return;
    }
    if (idDestino == -1) {
        QMessageBox::warning(this, "Erro", "Rua de destino não encontrada no mapa.");
        return;
    }

    // 4. EXECUTA O DIJKSTRA (Cálculo Pesado)
    double distancia = meuGrafo->dijkstra(idOrigem, idDestino);

    // 5. MOSTRA O RESULTADO
    if (distancia >= 0) {
        QString msg = "Rota Encontrada!\n\n";
        msg += "De: " + origemTexto + "\n";
        msg += "Para: " + destinoTexto + "\n";

        // Formata para Km ou Metros
        if (distancia > 1000) {
            msg += "Distância: " + QString::number(distancia / 1000.0, 'f', 2) + " km";
        } else {
            msg += "Distância: " + QString::number(distancia, 'f', 0) + " metros";
        }

        ui->labelResultado->setText(msg);
    } else {
        ui->labelResultado->setText("Não existe caminho possível entre estes locais.");
        QMessageBox::information(this, "Sem Rota", "Os pontos estão isolados.");
    }
}
