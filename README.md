# Trabalho Final: Rotas Pelotas | Disciplina Algoritmos e Estruturas de Dados II.

## Integrantes
- Gabriel Almeida
- Lemoel da Costa

## Como Abrir e Rodar
1. **Abrir**: Inicie o Qt Creator e vá em: Arquivo > Abrir Arquivo ou Projeto. Selecione o arquivo TrabalhoFinal.pro.
2. **Configurar**: Escolha o kit apropriado (ex: Desktop Qt 5.15 ou 6.x) e clique em Configure Project.
3. **Dados**: Certifique-se de que a pasta ArqJSON esteja no mesmo diretório do executável (ou conforme configurado no DataManager) para que o mapa carregue corretamente.
4. **Executar**: Clique no botão de "Play" (ícone verde) ou pressione Ctrl + R.

## Estruturas de Dados
- **Grafo (Lista de Adjacência)**: Armazena os cruzamentos (nós) e ruas (arestas) de Pelotas. Utiliza o "Algoritmo de Dijkstra" para encontrar o menor caminho.
- **Árvore Trie**: Indexação dos nomes das ruas, permitindo buscas rápidas e funcionalidade de autocompletar na interface.
- **Unordered Map**: Mapeamento eficiente entre IDs de nós, coordenadas geográficas e nomes de ruas para acesso rápido durante a execução.
- **JSON**: Base de dados externa para persistência da malha urbana.
