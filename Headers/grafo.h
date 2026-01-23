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
public:
    Grafo();
    void adicionarAresta(long long u, long long v, double peso);
    double dijkstra(long long primeiroNodo, long long ultimoNodo);
};

