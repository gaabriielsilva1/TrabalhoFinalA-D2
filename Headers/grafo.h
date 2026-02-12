#pragma once
#include <QGeoCoordinate>
#include <vector>
#include <unordered_map>
#include <string>
#include <Qstring>


//para desenho do mapa
struct Nodo {
    double x; //longitude
    double y; //latitude
};

struct Aresta {
    long long destino;
    double peso; //distancia
};

class Grafo {
private:
    std::unordered_map<long long, std::vector<Aresta>> listaAdj;
    //traduz o texto da rua para ids
    std::unordered_map<std::string, std::vector<long long>> mapaNomes;
    //traduz caminho do djkstra pra texto
    std::unordered_map<long long, std::string> mapaIdsParaNomes;
    //para o desenho do mapa
    std::unordered_map<long long, Nodo> mapaNodos;
public:
    Grafo();
    void adicionarAresta(long long u, long long v, double peso);
    //vetor com os ids do caminho
    //distância total em double
    std::pair<std::vector<long long>, double> dijkstra(long long origem, long long destino);
    long long getIdByName(QString nomeRua);
    void adicionarNodo(long long id, double x, double y);//para ajudar no desenho

    QGeoCoordinate obterCoordenada(long long id); //desenho do mapa

    std::vector<std::string> getTodasRuas();

    void associarNomeAoId(std::string nome, long long id); //usada pelo DataManager

    QString getNameById(long long id);
};


