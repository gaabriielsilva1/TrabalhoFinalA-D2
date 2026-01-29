#include "Headers/trie.h"
#include <iostream>

Trie::Trie(){
  root = new TrieNode();
}

Trie::~Trie(){
  clear(root);
}

void Trie::clear(TrieNode* node){
  if(node == nullptr) return;

  for(auto& pair : node->children){
    clear(pair.second);
  }

  delete node;
}

void Trie::insert(const std::string& word){
  TrieNode* current = root;

  for(char ch : word){
    if(current->children.find(ch) == current -> children.end()){
      current->children[ch] = new TrieNode();
    }
    current = current->children[ch]
  }
  current->ehFim = true;
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    TrieNode* current = root;
    std::vector<std::string> results;

    // 1. Navega até o final do prefixo digitado pelo usuário
    for (char ch : prefix) {
        // Se em algum momento o caminho não existir, retorna lista vazia
        if (current->children.find(ch) == current->children.end()) {
            return results; 
        }
        current = current->children[ch];
    }

    // 2. A partir do nó onde paramos, busca todas as palavras possíveis abaixo dele
    collectSuggestions(current, prefix, results);
    
    return results;
}


