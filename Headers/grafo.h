#pragma once
#include <QGeoCoordinate>
#include <vector>
#include <unordered_map>
#include <string>
#include <Qstring>
#include <queue>
#include <limits>

//para desenho do mapa
struct Nodo {
    double x; // Longitude
    double y; // Latitude
};

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

    std::unordered_map<long long, Nodo> mapaNodos; //para o desenho do mapa
public:
    Grafo();
    void adicionarAresta(long long u, long long v, double peso);
    // Retorna um PAR:
    // 1º item (first) = Vetor com os IDs do caminho (para o Mapa)
    // 2º item (second) = Distância total em double (para o Label)
    std::pair<std::vector<long long>, double> dijkstra(long long origem, long long destino);
    void adicionarNodo(long long id, double x, double y);//para ajudar no desenho

    QGeoCoordinate obterCoordenada(long long id); //desenho do mapa

    std::vector<std::string> getTodasRuas();

    void associarNomeAoId(std::string nome, long long id); // Usada pelo DataManager

    long long getIdByName(QString nomeRua); // Usada pela Interface Gráfica
    QString getNameById(long long id);
};


