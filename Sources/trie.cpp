#include "Headers/trie.h"

// CONSTRUTOR
Trie::Trie(){
    raiz = new TrieNode();
}

// DESTRUTOR
Trie::~Trie(){
    limpar(raiz);
}

// LIMPAR (Privado)
void Trie::limpar(TrieNode* node){
    if(node == nullptr) return;

    for(auto& pair : node->filhos){
        limpar(pair.second);
    }

    delete node;
}

// INSERIR
void Trie::inserir(const std::string& word){
    TrieNode* current = raiz;

    for(char ch : word){
        if(current->filhos.find(ch) == current -> filhos.end()){
            current->filhos[ch] = new TrieNode();
        }
        current = current->filhos[ch];
    }
    current->ehFim = true;
}

// AUTOCOMPLETE
std::vector<std::string> Trie::autoComplete(const std::string& prefix) {
    TrieNode* current = raiz;
    std::vector<std::string> results;

    // 1. Navega até o final do prefixo
    for (char ch : prefix) {
        if (current->filhos.find(ch) == current->filhos.end()) {
            return results;
        }
        current = current->filhos[ch];
    }

    // 2. A partir dali, coleta tudo o que tem pra baixo
    coletarSugestoes(current, prefix, results);

    return results;
}

// COLETAR SUGESTÕES (A peça que faltava!)
void Trie::coletarSugestoes(TrieNode* node, std::string prefixoAtual, std::vector<std::string>& resultados) {
    if (node->ehFim) {
        resultados.push_back(prefixoAtual);
    }

    for (auto const& pair : node->filhos) {
        coletarSugestoes(pair.second, prefixoAtual + pair.first, resultados);
    }
}
