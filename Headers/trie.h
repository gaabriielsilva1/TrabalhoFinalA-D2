#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> filhos;
    bool ehFim;
    TrieNode() : ehFim(false){}
};

class Trie {
private:
    TrieNode* raiz;
    void limpar(TrieNode* node);
    void coletarSugestoes(TrieNode* node, std::string prefixoAtual, std::vector<std::string>& resultados);

public:
    Trie();
    ~Trie();

    void inserir(const std::string& word);
    std::vector<std::string> autoComplete(const std::string& prefixo);
};

