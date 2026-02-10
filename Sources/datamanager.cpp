#include "../Headers/datamanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>
#include <QDir>

DataManager::DataManager() {}

/*
======================
PARA LER TODOS OS ARQ
======================
*/

bool DataManager::carregarTodosArquivos(QString pastaRaiz, Trie* trie, Grafo* grafo) {
    qDebug() << "Iniciando leitura dos arquivos na pasta:" << pastaRaiz;

    /*
    ===================
    PARA LER EDGES.JSON
    ===================
    */

    QFile fileEdges(pastaRaiz + "/edges.json");
    if (!fileEdges.open(QIODevice::ReadOnly)) {
        qDebug() << "Erro: Não foi encontrado edges.json";
        return false;
    }

    QJsonArray arrayArestas = QJsonDocument::fromJson(fileEdges.readAll()).array();

    for (const QJsonValue &valor : arrayArestas) {
        QJsonObject obj = valor.toObject();
        long long u = obj["u"].toVariant().toLongLong();
        long long v = obj["v"].toVariant().toLongLong();
        double distancia = obj["length"].toDouble();
        if(distancia == 0 && obj.contains("data")) {
            distancia = obj["data"].toObject()["length"].toDouble();
        }

        //ARRUMAR AQUIIIIIIIIIIIIIII
        if (distancia > 0) {
            grafo->adicionarAresta(u, v, distancia);
            // Assumindo que o mapa é mão dupla (se tiver info de oneway, adicione a lógica aqui)
            grafo->adicionarAresta(v, u, distancia);
        } else {
            qDebug() << "Aresta entre" << u << "e" << v << "com distância zero!";
        }
    }
    fileEdges.close();
    qDebug() << "Ruas carregada.";

    /*
    =======================
    LER LABEL_TO_NODES.JSON
    =======================
    */

    QFile fileLabel(pastaRaiz + "/label_to_nodes.json");
    if (fileLabel.open(QIODevice::ReadOnly)) {
        QJsonObject objLabel = QJsonDocument::fromJson(fileLabel.readAll()).object();

        //itera por todos os nomes de rua
        for (auto it = objLabel.begin(); it != objLabel.end(); ++it) {
            QString nomeCompleto = it.key().toLower();
            QJsonArray listaIds = it.value().toArray();
            //divide o cruzamento em nomes separados
            QStringList nomesIndividuais = nomeCompleto.split(" x ");
            for (const QString &nomeRua : nomesIndividuais) {
                //limpa espaços e garante minúsculo
                std::string ruaLimpa = nomeRua.trimmed().toStdString();

                //adiciona na Trie para o autocomplete aparecer
                trie->inserir(ruaLimpa);

                //vincula cada rua individual aos ids no grafo
                for(const QJsonValue& idVal : listaIds) {
                    long long idNode = idVal.toVariant().toLongLong();
                    grafo->associarNomeAoId(ruaLimpa, idNode);
                }
            }
        }
        fileLabel.close();
        qDebug() << "Nomes de busca carregados.";
    }else {
        qDebug() << "Aviso: label_to_nodes.json não encontrado. A busca por nome vai falhar.";
    }

    /*
    ==============
    LER NODES.JSON
    ==============
    */

    QFile fileNodes(pastaRaiz + "/nodes.json");
    if (fileNodes.open(QIODevice::ReadOnly)) {
        QJsonArray arrayNodes = QJsonDocument::fromJson(fileNodes.readAll()).array();

        for (const QJsonValue &valor : arrayNodes) {
            QJsonObject obj = valor.toObject();
            long long id = obj["id"].toVariant().toLongLong();
            double lon = obj["x"].toDouble();
            double lat = obj["y"].toDouble();

            //carrega o grafo com a posição fisica
            grafo->adicionarNodo(id, lon, lat);
        }
        fileNodes.close();
    }
    return true;
}
