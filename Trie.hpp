#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include "Game.hpp"

const int ALPHABET_SIZE = 36; // 26 letras + 10 números

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode();
};

class Trie {
private:
    TrieNode* root;

public:
    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);
    std::vector<Game*> autocomplete(std::string prefix, int k);
    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game*>& games);

    // outros métodos auxiliares, se necessário
    void find_games(std::vector<Game*>& games, TrieNode* node);
};

#endif