#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include "grafo.h"
#include "trie.h"

class DataManager {
public:
    DataManager();

    // Agora recebe o CAMINHO DA PASTA, pois vai buscar 3 arquivos lá dentro
    bool carregarTodosArquivos(QString pastaRaiz, Trie* trie, Grafo* grafo);
};

#endif // DATAMANAGER_H
