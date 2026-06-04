#include <iostream>
#include <string>
#include <cstdlib> // Importado para usar o std::atoi
#include <vector>
#include "Trie.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char* argv[]) {
    // 1. Valida os argumentos do terminal
    if (argc != 3) {
        std::cout << "Usage: ./app k prefix" << std::endl;
        return 1;
    }

    // 2. Extrai k, converte-o para inteiro e extrai o prefixo
    int k = std::atoi(argv[1]);
    std::string prefix = argv[2];

    // 3. Instancia a Trie
    Trie trie;

    // 4. Insere a base de dados na árvore (usando ponteiros do array global)
    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    // 5. Executa a busca
    std::vector<Game*> results = trie.autocomplete(prefix, k);

    // 6. Imprime os resultados seguindo a regra estrita de formatação
    if (results.empty()) {
        std::cout << "No results found" << std::endl;
    } else {
        for (Game* g : results) {
            std::cout << g->getTitle() << " | " << g->getShortDescription() << " | " << g->getPopularity() << std::endl;
        }
    }

    return 0;
}