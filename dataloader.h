#ifndef DATALOADER_H
#define DATALOADER_H

#include <QString>
#include "trie.h"
#include "grafo.h"

class DataLoader {
public:
    // Carrega os arquivos e preenche a Trie e o Grafo [cite: 19]
    static void carregarDados(QString path, Trie& trie, Grafo& grafo);
};

#endif
