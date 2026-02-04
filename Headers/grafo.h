#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <Qstring>
#include <queue>
#include <limits>

struct Aresta {
    long long destino;
    double peso; // Distância
};

class Grafo {
private:
    //LISTA DE ADJACÊNCIA:
    //ID ORIGIM -> Lista de adjacência
    std::unordered_map<long long, std::vector<Aresta>> listaAdj; //Mapa: ID do nó -> Lista de Arestas

    //DICIONARIO NOME-ID:
    //TRADUZ O TEXTO DA RUA PARA ID's UTILIZADOS NO CÓDIGO
    std::unordered_map<std::string, std::vector<long long>> mapaNomes;

    //DICIONARIO ID-NOME:
    //TRADUZ O CAMINHO DO DIJKSTRA PARA TEXTO
    std::unordered_map<long long, std::string> mapaIdsParaNomes;
public:
    Grafo();
    void adicionarAresta(long long u, long long v, double peso);
    double dijkstra(long long primeiroNodo, long long ultimoNodo);

    std::vector<std::string> getTodasRuas();

    void associarNomeAoId(std::string nome, long long id); // Usada pelo DataManager

    long long getIdByName(QString nomeRua); // Usada pela Interface Gráfica
    QString getNameById(long long id);

};


