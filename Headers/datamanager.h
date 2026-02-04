#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include "grafo.h"
#include "trie.h"

class DataManager {
public:
    DataManager();

    // Agora recebe o CAMINHO DA PASTA, pois vai buscar 3 arquivos lá dentro
    bool carregarTodosArquivos(const QString& pastaRaiz, Grafo& grafo, Trie& trie);
};

#endif // DATAMANAGER_H
