#pragma once

#include <unordered_map>
#include <string>
#include <vector>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> filhos; //tabela Hash que vai ter o caracter como chave
    bool ehFim;
    TrieNode() : ehFim(false){}
};

class Trie {
private:
    TrieNode* raiz; //cria a raiz
    void limpar(TrieNode* node); //limpa um nodo


public:
    Trie();//construtor
    ~Trie(); //destrutor
    void coletarSugestoes(TrieNode* node, std::string prefixoAtual, std::vector<std::string>& resultados);
    void inserir(const std::string& word);
    std::vector<std::string> autoComplete(const std::string& prefixo);
    bool contem(const std::string& word);
};

