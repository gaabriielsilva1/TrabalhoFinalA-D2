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
    std::unordered_map<long long, std::vector<Aresta>> listaAdj; //tabela hash, que vai receber como chave um long, e de resposta uma lista de Aresta
    //traduz o texto da rua para ids
    std::unordered_map<std::string, std::vector<long long>> mapaNomes; //tabela  hash, como chave o nome de uma rua, e de resposta cada id q existe naquela rua
    //traduz caminho do djkstra pra texto
    std::unordered_map<long long, std::string> mapaIdsParaNomes; //tabela hash, como chave long(id), e resposta o nome da rua
    //para o desenho do mapa
    std::unordered_map<long long, Nodo> mapaNodos; //tabela hash, chave o id, e vai ter um nodo com posição do id
public:
    Grafo();
    void adicionarAresta(long long u, long long v, double peso);
    //vetor com os ids do caminho
    //distância total em double
    std::pair<std::vector<long long>, double> dijkstra(long long origem, long long destino);

    void adicionarNodo(long long id, double x, double y);//para ajudar no desenho

    QGeoCoordinate obterCoordenada(long long id); //desenho do mapa

    std::vector<std::string> getTodasRuas();

    void associarNomeAoId(std::string nome, long long id); //usada pelo DataManager


    QString getNameById(long long id);
};


