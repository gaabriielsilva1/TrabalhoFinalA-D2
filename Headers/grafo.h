#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

struct Aresta {
    long long destino;
    double peso; // Distância
};

class Grafo {
private:
    std::unordered_map<long long, std::vector<Aresta>> listaAdj; //Mapa: ID do nó -> Lista de Arestas

    std::unordered_map<std::string, std::vector<long long>> mapaNomes;
public:
    Grafo();
    void adicionarAresta(long long u, long long v, double peso);
    double dijkstra(long long primeiroNodo, long long ultimoNodo);
    void associarNomeAoId(std::string nome, long long id); // Usada pelo DataManager
    long long getIdByName(QString nomeRua); // Usada pela Interface Gráfica
};


