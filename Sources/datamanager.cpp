#include "../Headers/datamanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant> // Importante para converter IDs grandes
#include <QDebug>

DataManager::DataManager() {
}

bool DataManager::carregarDados(const QString& caminhoArquivo, Grafo& grafo, Trie& trie) {
    QFile file(caminhoArquivo);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erro crítico: Não foi possível abrir o arquivo:" << caminhoArquivo;
        return false;
    }

    QByteArray dados = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(dados);
    
    // O seu arquivo começa com colchetes [ ... ], então é um Array direto
    QJsonArray arrayArestas = doc.array(); 

    qDebug() << "Carregando" << arrayArestas.size() << "arestas do OpenStreetMap...";

    for (const QJsonValue &valor : arrayArestas) {
        QJsonObject obj = valor.toObject();

        // 1. Pegar IDs dos Nós (u = origem, v = destino)
        // IDs do OSM são grandes, use toLongLong()
        long long u = obj["u"].toVariant().toLongLong();
        long long v = obj["v"].toVariant().toLongLong();

        // 2. Acessar o objeto "data" onde estão os detalhes
        QJsonObject dataObj = obj["data"].toObject();
        
        // Extrair propriedades
        double distancia = dataObj["length"].toDouble();
        QString nomeRua = dataObj["name"].toString();
        bool maoUnica = dataObj["oneway"].toBool();

        // Validação básica
        if (distancia > 0) {
            // Adiciona aresta de ida (u -> v)
            grafo.adicionarAresta(u, v, distancia);

            // SE NÃO FOR MÃO ÚNICA, adiciona a volta também (v -> u)
            if (!maoUnica) {
                grafo.adicionarAresta(v, u, distancia);
            }

            // Tratamento do Nome (Trie e Busca)
            // Algumas ruas no JSON podem vir sem nome ou null
            if (!nomeRua.isEmpty() && nomeRua != "null") {
                std::string nomeStd = nomeRua.toStdString();

                trie.insert(nomeStd);
                
                // Associa o nome ao nó de origem (u)
                grafo.associarNomeAoId(nomeStd, u);
                
                // Se for mão dupla, podemos associar ao nó (v) também para facilitar a busca
                if (!maoUnica) {
                    grafo.associarNomeAoId(nomeStd, v);
                }
            }
        }
    }

    file.close();
    qDebug() << "Leitura concluída! Grafo e Trie populados.";
    return true;
}
