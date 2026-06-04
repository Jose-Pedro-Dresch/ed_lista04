#include "Trie.hpp"
using namespace std;

TrieNode::TrieNode(){
    this->isEndOfTitle = false;
    this->game = nullptr;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->children[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (children[i] != nullptr) {
            delete children[i];
        }
    }
}

Trie::Trie(){
    this->root = new TrieNode();
}

Trie::~Trie() {
    delete this->root;
}

std::string Trie::toSearchKey(std::string text) {
    std::string final_word = "";
    for (char c : text) {
        if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122)) {
            final_word += c; // Cola números e letras minúsculas
        } else if (c >= 65 && c <= 90) {
            final_word += (c + 32); // Converte maiúscula para minúscula e cola
        }
        // Espaços e outros símbolos caem fora dos ifs e são ignorados
    }
    return final_word;
}

bool Trie::insert(Game* game){
    string title = this->toSearchKey(game->getTitle());

    TrieNode* current = root;

    for(char c : title){
        int i;
        if(c >= 97 && c <= 122){
            i = c - 97;
        } else if (c >= 48 && c <= 57) { 
            i = c - 22;
        }

        if(current->children[i] == nullptr){
            current->children[i] = new TrieNode();
        } 
        current = current->children[i];
    }
    if (current->isEndOfTitle) {
            return false; // Jogo já existe, recusa a inserção
    }
    current->isEndOfTitle = true;
    current->game = game;

    return true; 
}

bool Trie::contains(std::string title){
    title = this->toSearchKey(title);

    TrieNode* current = root;

    for(char c : title){
        int i;
        if(c >= 97 && c <= 122){
            i = c - 97;
        } else if (c >= 48 && c <= 57) { 
            i = c - 22;
        }

        if(current->children[i] == nullptr){
            return false;
        } 
        current = current->children[i];
    }
    return current->isEndOfTitle;
}


void Trie::sortResults(std::vector<Game*>& games){
    int n = games.size();
    int i, j;                        
    Game* current;
    for (i = 1; i < n; i++) {                  
        current = games[i];                      
        j = i - 1;                         

        while (j >= 0){   
            bool swapGames = false;

            if(games[j]->getPopularity() < current->getPopularity()){
                swapGames = true;
            }
            else if (games[j]->getPopularity() == current->getPopularity()){
                string title_current = this->toSearchKey(current->getTitle());
                string title_j = this->toSearchKey(games[j]->getTitle());

                if(title_j > title_current){
                    swapGames = true;
                }
            }

            if(swapGames){
                games[j+1] = games[j];                
                j = j - 1;    
            } else {
                break;
            }
        }
        games[j+1] = current;                    
    }
}


void Trie::find_games(std::vector<Game*>& games, TrieNode* node){
    if(node == nullptr){
        return;
    }
    if(node->isEndOfTitle){
        games.push_back(node->game);
    }

    for(int i = 0; i<36; i++){
        if (node->children[i] != nullptr) {
            this->find_games(games, node->children[i]);
        }
    }
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k){
    std::vector<Game*> games;

    if(k<=0){
        return games;
    }

    prefix = this->toSearchKey(prefix);

    TrieNode* current = root;

    for(char c : prefix){
            int i;
        if(c >= 97 && c <= 122){
            i = c - 97;
        } else if (c >= 48 && c <= 57) { 
            i = c - 22;
        }

        if (current->children[i] == nullptr) {
            return games;
        }

        current = current->children[i];
    }

    this->find_games(games, current);
    this->sortResults(games);

    if (games.size() > k) {
        games.resize(k);
    }

    return games;
}