#include "Headers/grafo.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <utility>

Grafo::Grafo(){
}

/*
==========
ADD ARESTA
==========
*/

void Grafo::adicionarAresta(long long u, long long v, double peso){
    listaAdj[u].push_back({v, peso});
}

/*
========================
ASSOCIACAO DO NOME AO ID
========================
*/

void Grafo::associarNomeAoId(std::string nome, long long id) {
    //guarda o id na lista dessa rua
    mapaNomes[nome].push_back(id);
}

/*
==============================================
RETORANR O ID APARTIR DO NOME
==============================================
*/

long long Grafo::getIdByName(QString nomeRua) {
    std::string nomeStd = nomeRua.toLower().trimmed().toStdString();
    if (mapaNomes.find(nomeStd) != mapaNomes.end()) {
        return mapaNomes[nomeStd].front();
    }

    return -1;
}

/*
==============================================
RETORNA AS RUAS E PEGA AS CHAVES DO DICIONARIO
==============================================
*/

std::vector<std::string> Grafo::getTodasRuas() {
    std::vector<std::string> listaRuas;


    //pegar o nome da rua
    for (auto const& [nome, ids] : mapaNomes) {
        listaRuas.push_back(nome); //guarda o nome na lista
    }

    return listaRuas; //manda a lista para o mainwindow
}

/*
=================================
PARA CALCULAR E AJUDAR NO CAMINHO
=================================
*/

std::pair<std::vector<long long>, double> Grafo::dijkstra(long long primeiroNodo, long long ultimoNodo) {

    //fila de prioridade para pegar sempre a menor distância
    std::priority_queue<std::pair<double, long long>,
                        std::vector<std::pair<double, long long>>,
                        std::greater<>> pq;

    std::unordered_map<long long, double> distancia;
    std::unordered_map<long long, long long> anterior;

    //inicializa usando mapaNodos para garantir que todos os pontos comecem como infinito.
    for(auto const& [id, coord] : mapaNodos) {
        distancia[id] = std::numeric_limits<double>::infinity();
    }

    // Se o ponto de partida não existe no mapa, cancela
    if (distancia.find(primeiroNodo) == distancia.end()) return {{}, -1.0};

    distancia[primeiroNodo] = 0;
    pq.push({0, primeiroNodo});

    double dFinal = -1.0;

    while (!pq.empty()) {
        double d = pq.top().first;
        long long u = pq.top().second;
        pq.pop();

        if (u == ultimoNodo) {
            dFinal = d;
            break;
        }

        if (d > distancia[u]) continue;

        //verifica se o nó 'u' tem vizinhos na lista de adjacência
        if (listaAdj.count(u)) {
            for (auto& aresta : listaAdj[u]) {
                if (distancia[u] + aresta.peso < distancia[aresta.destino]) {
                    distancia[aresta.destino] = distancia[u] + aresta.peso;
                    anterior[aresta.destino] = u;
                    pq.push({distancia[aresta.destino], aresta.destino});
                }
            }
        }
    }

    //reconstruçao do Caminho
    std::vector<long long> caminho;
    if (dFinal != -1.0) {
        long long atual = ultimoNodo;
        while (atual != primeiroNodo) {
            caminho.push_back(atual);
            if (anterior.find(atual) == anterior.end()) break;
            atual = anterior[atual];
        }
        caminho.push_back(primeiroNodo);
        std::reverse(caminho.begin(), caminho.end());
    }

    return {caminho, dFinal};
}

/*
======================
USADA PELO DATAMANAGER
======================
*/

void Grafo::adicionarNodo(long long id, double x, double y) {
    mapaNodos[id] = {x, y};
}

/*
====================
USADO PELA INTERFACE
====================
*/

QGeoCoordinate Grafo::obterCoordenada(long long id) {
    if (mapaNodos.count(id)) {
        //y é latitude e x longitude
        return QGeoCoordinate(mapaNodos[id].y, mapaNodos[id].x);
    }
    return QGeoCoordinate(); //retorna vazio se não encontrar
}
