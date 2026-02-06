#include "../Headers/datamanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>
#include <QDir>

DataManager::DataManager() {}

bool DataManager::carregarTodosArquivos(QString pastaRaiz, Trie* trie, Grafo* grafo) {
    qDebug() << "Iniciando leitura dos arquivos na pasta:" << pastaRaiz;

    // ==============================================================================
    // ETAPA 1: LER EDGES.JSON (O Esqueleto do Grafo)
    // ==============================================================================
    QFile fileEdges(pastaRaiz + "/edges.json");
    if (!fileEdges.open(QIODevice::ReadOnly)) {
        qDebug() << "Erro fatal: Faltando edges.json";
        return false;
    }

    QJsonArray arrayArestas = QJsonDocument::fromJson(fileEdges.readAll()).array();

    for (const QJsonValue &valor : arrayArestas) {
        QJsonObject obj = valor.toObject();
        // Nota: Nesse formato separado, 'u' e 'v' costumam estar na raiz do objeto, não em 'data'
        // Se der erro de leitura, verifique se seu json tem 'u' direto ou dentro de 'data'
        long long u = obj["u"].toVariant().toLongLong();
        long long v = obj["v"].toVariant().toLongLong();

        // As vezes o length está direto, as vezes dentro de 'data'. Tenta os dois.
        double distancia = obj["length"].toDouble();
        if(distancia == 0 && obj.contains("data")) {
            distancia = obj["data"].toObject()["length"].toDouble();
        }

        if (distancia > 0) {
            grafo->adicionarAresta(u, v, distancia);
            // Assumindo que o mapa é mão dupla (se tiver info de oneway, adicione a lógica aqui)
            grafo->adicionarAresta(v, u, distancia);
        }
    }
    fileEdges.close();
    qDebug() << "Topologia (Ruas) carregada.";

    // ==============================================================================
    // ETAPA 2: LER LABEL_TO_NODES.JSON (Preencher a Trie e a Busca)
    // Estrutura: "Nome da Rua": [ID1, ID2, ID3...]
    // ==============================================================================
    QFile fileLabel(pastaRaiz + "/label_to_nodes.json");
    if (fileLabel.open(QIODevice::ReadOnly)) {
        QJsonObject objLabel = QJsonDocument::fromJson(fileLabel.readAll()).object();

        // Itera por todos os nomes de rua
        for (auto it = objLabel.begin(); it != objLabel.end(); ++it) {
            QString nomeRua = it.key().toLower(); //Pega a rua "n sei o que x sei la"
            std::string nomeStd = nomeRua.toStdString();
            QStringList nomesIndividuais = nomeRua.split(" x ");

            for (const QString &nomeRua : nomesIndividuais) {
                //LIMPA ESPAÇOS SOBRANDO E INSERE CADA RUA NA TRIE
                std::string ruaLimpa = nomeRua.trimmed().toStdString();
            //Adiciona na Trie (Autocomplete)
                trie->inserir(ruaLimpa);
            }
            // 2. Pega a lista de IDs dessa rua
            QJsonArray listaIds = it.value().toArray();
            for(const QJsonValue& idVal : listaIds) {
                long long idNode = idVal.toVariant().toLongLong();
                // Associa esse nome a esse ID no Grafo
                grafo->associarNomeAoId(nomeStd, idNode);
            }
        }
        fileLabel.close();
        qDebug() << "Nomes de busca carregados.";
    }else {
        qDebug() << "Aviso: label_to_nodes.json não encontrado. A busca por nome vai falhar.";
    }
    return true;
}
