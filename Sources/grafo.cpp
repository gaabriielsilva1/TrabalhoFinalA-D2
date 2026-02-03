#include "Headers/grafo.h"
#include <queue>
#include <limits>

Grafo::Grafo(){

}

void Grafo::adicionarAresta(long long u, long long v, double peso){
    listaAdj[u].push_back({v, peso});
}

void Grafo::associarNomeAoId(std::string nome, long long id) {
    // Guarda o ID na lista dessa rua
    mapaNomes[nome].push_back(id);
}

long long Grafo::getIdByName(QString nomeRua) {
    // 1. Converte QString (Qt) para std::string (C++ Padrão)
    std::string nomeStd = nomeRua.toStdString();

    // 2. Verifica se a rua existe no mapa
    if (mapaNomes.find(nomeStd) != mapaNomes.end()) {
        // 3. Retorna o primeiro ID registrado para essa rua (geralmente o início dela)
        // Como o vetor guarda vários IDs, pegamos o índice [0] ou .front()
        return mapaNomes[nomeStd].front();
    }

    // 4. Se não achou, retorna -1 (sinal de erro para a GUI tratar)
    return -1;
}

double Grafo::dijkstra(long long primeiroNodo, long long ultimoNodo){
    // Priority Queue para pegar sempre o menor caminho atual
    // Par: <distância acumulada, ID do nó>

    std::priority_queue<std::pair<double,long long>,
                        std::vector<std::pair<double, long long>>,
                        std::greater<>> pq;

    std::unordered_map<long long, double> distancia;

    for(auto const& [id, Aresta] : listaAdj){
        distancia[id] = std::numeric_limits<double>::infinity();
    }

    distancia[primeiroNodo] = 0;
    pq.push({0, primeiroNodo});

    while (!pq.empty()){
        double d = pq.top().first;
        long long u = pq.top().second;
        pq.pop();

        if (u == ultimoNodo) return d;
        if (d > distancia[u]) continue;

        if (listaAdj.find(u) != listaAdj.end()){
            for(auto& Aresta : listaAdj[u]){
                if(distancia[u] + Aresta.peso < distancia[Aresta.destino]){
                    distancia[Aresta.destino] = distancia[u] + Aresta.peso;
                    pq.push({distancia[Aresta.destino], Aresta.destino});
                }
            }
        }

    }
    return -1;
}


