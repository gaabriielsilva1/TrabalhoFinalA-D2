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

    QFile fileEdges(pastaRaiz + "/edges.json"); //criando um objeto chamado fileEdges
    if (!fileEdges.open(QIODevice::ReadOnly)) {//vai avisar que quer abrir o arq
        qDebug() << "Não foi encontrado edges.json";
        return false;
    }

    QJsonArray arrayArestas = QJsonDocument::fromJson(fileEdges.readAll()).array();
    for (const QJsonValue &valor : arrayArestas) { //vamos percorrer o array q criamos
        QJsonObject obj = valor.toObject(); //cada valor sera do array sera transformado em um obj,representa uma unica rua
        long long u = obj["u"].toVariant().toLongLong();
        long long v = obj["v"].toVariant().toLongLong();
        double distancia = obj["length"].toDouble();
        bool oneway = false;

        if (obj.contains("data")) {
            QJsonObject data = obj["data"].toObject();
            if (distancia == 0) distancia = data["length"].toDouble();

            //verifica se é mao unica
            oneway = data["oneway"].toVariant().toBool();
        } else {
            //se estiver na raiz do objeto
            oneway = obj["oneway"].toVariant().toBool();
        }

        if (distancia > 0) {
            //smpre adiciona o sentido de u para v
            grafo->adicionarAresta(u, v, distancia);

            //so adiciona a volta se nao for mao unica
            if (!oneway) {
                grafo->adicionarAresta(v, u, distancia);
            }
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

        for (auto it = objLabel.begin(); it != objLabel.end(); ++it) {
            QString nomeOriginal = it.key().toLower().trimmed();
            QJsonArray listaIds = it.value().toArray();

            //inserir o cruzamento completo
            std::string strOriginal = nomeOriginal.toStdString();
            trie->inserir(strOriginal);

            //vincular ao Grafo
            for(const QJsonValue& idVal : listaIds) {
                grafo->associarNomeAoId(strOriginal, idVal.toVariant().toLongLong());
            }

            //quebrar o nome para variações
            QStringList partes = nomeOriginal.split(" x ");
            if (partes.size() == 2) {
                QString ruaA = partes[0].trimmed();
                QString ruaB = partes[1].trimmed();

                //versão Invertida(rua B x rua A)
                QString nomeInvertido = ruaB + " x " + ruaA;
                std::string strInvertida = nomeInvertido.toStdString();
                trie->inserir(strInvertida);

                //se o nome começar com "rua ", insere também sem o "rua "
                if(ruaA.startsWith("rua ")) trie->inserir(ruaA.mid(4).trimmed().toStdString());
                if(ruaB.startsWith("rua ")) trie->inserir(ruaB.mid(4).trimmed().toStdString());

                //vincular todas essas variações ao mesmo id no Grafo
                for(const QJsonValue& idVal : listaIds) {
                    long long idNode = idVal.toVariant().toLongLong();
                    grafo->associarNomeAoId(strInvertida, idNode);
                    grafo->associarNomeAoId(ruaA.toStdString(), idNode);
                    grafo->associarNomeAoId(ruaB.toStdString(), idNode);
                }
            }
        }
        fileLabel.close();
        qDebug() << "Nomes e variações carregados.";
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
