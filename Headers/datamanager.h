ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include "grafo.h"
#include "trie.h"

class DataManager {
public:
    DataManager();
    
    // Retorna true se carregou com sucesso, false se deu erro no arquivo
    bool carregarDados(const QString& caminhoArquivo, Grafo& grafo, Trie& trie);
};

#endif // DATAMANAGER_H
