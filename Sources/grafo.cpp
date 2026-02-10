#include "Headers/grafo.h"
#include <algorithm>

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
    //converte qstring para std::string
    std::string nomeStd = nomeRua.toStdString();

    //verifica se a rua existe no mapa
    if (mapaNomes.find(nomeStd) != mapaNomes.end()) {
        //retorna primeiro id registrado do inicio dela
        return mapaNomes[nomeStd].front();
    }
    //se não achou
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

    return listaRuas; // manda a lista para o mainwindow
}

/*
=================================
PARA CALCULAR E AJUDAR NO CAMINHO
=================================
*/

std::pair<std::vector<long long>, double> Grafo::dijkstra(long long primeiroNodo, long long ultimoNodo) {

    //guarda <distância acumulada, id do nó>
    std::priority_queue<std::pair<double, long long>,
                        std::vector<std::pair<double, long long>>,
                        std::greater<>> pq;

    std::unordered_map<long long, double> distancia;
    std::unordered_map<long long, long long> anterior;//guarda o pai de cada no

    //inicia as distancias como infinito
    for(auto const& [id, lista] : listaAdj) {
        distancia[id] = std::numeric_limits<double>::infinity();
    }

    distancia[primeiroNodo] = 0;
    pq.push({0, primeiroNodo});

    double dFinal = -1.0;

    while (!pq.empty()) {
        double d = pq.top().first;
        long long u = pq.top().second;
        pq.pop();

        //se chegar no destino salva a distancia e para a busca
        if (u == ultimoNodo) {
            dFinal = d;
            break;
        }

        if (d > distancia[u]) continue;

        if (listaAdj.find(u) != listaAdj.end()) {
            for (auto& aresta : listaAdj[u]) {
                if (distancia[u] + aresta.peso < distancia[aresta.destino]) {
                    distancia[aresta.destino] = distancia[u] + aresta.peso;
                    anterior[aresta.destino] = u;
                    pq.push({distancia[aresta.destino], aresta.destino});
                }
            }
        }
    }

    /*
    ===================================
    PARA RECONSTRUIR A ROTA PARA O MAPA
    ===================================
    */

    std::vector<long long> caminho;

    if (dFinal != -1.0) { //se existe um caminho
        long long atual = ultimoNodo;
        while (atual != primeiroNodo) {
            caminho.push_back(atual);
            atual = anterior[atual]; //volta para o no anterior
        }
        caminho.push_back(primeiroNodo);

        //inverte o vetor para ficar na ordem Origem -> Destino
        std::reverse(caminho.begin(), caminho.end());
    }

    return {caminho, dFinal}; //retorna as duas informações
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
