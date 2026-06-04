#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include "Trie.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char* argv[]) {
    // Valida os argumentos do terminal
    if (argc != 3) {
        std::cout << "Usage: ./app k prefix" << std::endl;
        return 1;
    }

    // Extrai k, converte-o para inteiro e extrai o prefixo
    int k = std::atoi(argv[1]);
    std::string prefix = argv[2];

    // Instancia a Trie
    Trie trie;

    // Insere os games de GameDatabase na Trie
    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    //  Executa a busca pelo prefixo e k dados
    std::vector<Game*> results = trie.autocomplete(prefix, k);

    // Exibe os jogos obtidos
    if (results.empty()) {
        std::cout << "No results found" << std::endl;
    } else {
        for (Game* g : results) {
            std::cout << g->getTitle() << " | " << g->getShortDescription() << " | " << g->getPopularity() << std::endl;
        }
    }

    return 0;
}