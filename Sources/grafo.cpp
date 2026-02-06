#include "Headers/grafo.h"
#include <algorithm>
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

// RETORNA TODAS AS RUAS: PEGA AS CHAVES DO NOSSO DICIONÁRIO E CRIA UMA LISTA
std::vector<std::string> Grafo::getTodasRuas() {
    std::vector<std::string> listaRuas;

    // O mapaNomes guarda: "Nome da Rua" -> [ID1, ID2...]
    // Nós queremos só a parte do "Nome da Rua" (a chave do mapa)
    for (auto const& [nome, ids] : mapaNomes) {
        listaRuas.push_back(nome); // Guarda o nome na lista
    }

    return listaRuas; // Entrega a lista pronta para a MainWindow usar
}

//funcao nova
std::pair<std::vector<long long>, double> Grafo::dijkstra(long long primeiroNodo, long long ultimoNodo) {

    // Priority Queue: <distância acumulada, ID do nó>
    std::priority_queue<std::pair<double, long long>,
                        std::vector<std::pair<double, long long>>,
                        std::greater<>> pq;

    std::unordered_map<long long, double> distancia;
    std::unordered_map<long long, long long> anterior; // NOVO: Guarda o "pai" de cada nó

    // Inicializa as distâncias como infinito
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

        // Se chegamos no destino, salvamos a distância e paramos a busca
        if (u == ultimoNodo) {
            dFinal = d;
            break;
        }

        if (d > distancia[u]) continue;

        if (listaAdj.find(u) != listaAdj.end()) {
            for (auto& aresta : listaAdj[u]) {
                // Relaxamento da aresta
                if (distancia[u] + aresta.peso < distancia[aresta.destino]) {
                    distancia[aresta.destino] = distancia[u] + aresta.peso;

                    // NOVO: Salvamos que chegamos em 'destino' através de 'u'
                    anterior[aresta.destino] = u;

                    pq.push({distancia[aresta.destino], aresta.destino});
                }
            }
        }
    }

    // 2. RECONSTRUÇÃO DO CAMINHO (Backtracking)
    std::vector<long long> caminho;

    if (dFinal != -1.0) { // Se existe um caminho...
        long long atual = ultimoNodo;
        while (atual != primeiroNodo) {
            caminho.push_back(atual);
            atual = anterior[atual]; // Volta para o nó anterior
        }
        caminho.push_back(primeiroNodo);

        // Inverte o vetor para ficar na ordem: Origem -> Destino
        std::reverse(caminho.begin(), caminho.end());
    }

    return {caminho, dFinal}; // Retorna as duas informações
}

// USADA PELO DATAMANAGER: Salva x (lon) e y (lat) de Pelotas
void Grafo::adicionarNodo(long long id, double x, double y) {
    mapaNodos[id] = {x, y}; // mapaNodos deve estar declarado no seu grafo.h
}

// USADA PELA INTERFACE: Traduz o ID para o ponto no mapa
QGeoCoordinate Grafo::obterCoordenada(long long id) {
    if (mapaNodos.count(id)) {
        // No seu JSON, y costuma ser latitude e x longitude
        return QGeoCoordinate(mapaNodos[id].y, mapaNodos[id].x);
    }
    return QGeoCoordinate(); // Retorna vazio se não encontrar
}


