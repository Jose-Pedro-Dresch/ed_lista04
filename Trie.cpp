#include "Trie.hpp"
using namespace std;

//=====================================================================================================================
//                                                  Classe TrieNode
//=====================================================================================================================

// Construtor da TrieNode
TrieNode::TrieNode(){
    this->isEndOfTitle = false; // inicializa o indicador de fim de jogo com false
    this->game = nullptr;  // inicializa o ponteiro de game como nullptr

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->children[i] = nullptr; // inicializa o ponteiro de cada filho como nullptr
    }
}

// Destrutor da TrieNode
TrieNode::~TrieNode() {
    // Percorre todos os filhos existentes e chama o delete de cada um, por recursão
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (children[i] != nullptr) { 
            delete children[i];
        }
    }
}



//=====================================================================================================================
//                                                  Classe Trie 
//=====================================================================================================================

// Construtor da Trie
Trie::Trie(){
    this->root = new TrieNode(); // inicializa a raíz com uma TrieNode
}

// Destrutor da Trie
Trie::~Trie() {
    delete this->root; // chama o destrutor da raíz, que por sua vez chama o destrutor de seus filhos e assim por diante
}

// Método de conversão de um título para o padrão armazenado na Trie
std::string Trie::toSearchKey(std::string text) {
    std::string final_word = ""; // inicializa uma string vazia, para concatenar os caracteres passo a passo

    for (char c : text) {
        if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122)) { 
            final_word += c; // se for número ou letra minúscula contatena direto
        } else if (c >= 65 && c <= 90) {
            final_word += (c + 32); // Se for letra maiúscula converte para minúscula antes de concatenar
        }
        // Demais símbolos caem fora dos ifs e são ignorados
    }
    return final_word; // Retorna a string final limpa
}

// Método para inserir um jogo na Trie
bool Trie::insert(Game* game){
    string title = this->toSearchKey(game->getTitle()); // extrai o nome do jogo recebido e converte para o padrão ideal (minúsculas e algarismos)

    TrieNode* current = root; // inicializa um ponteiro na raiz, que vai caminhar pelos filhos

    for(char c : title){
        // Dado o caractere (letra minúscula ou algarismo), obtém a sua posição correspondente 
        // no array de filhos do nó. De 0-25 representa as letras e de 26-35 representa os algarismos
        int i;
        if(c >= 97 && c <= 122){
            i = c - 97;
        } else if (c >= 48 && c <= 57) { 
            i = c - 22;
        } else {
            continue; 
        }

        if(current->children[i] == nullptr){ // se no índice correspondente não houver TrieNode, inicializa uma nova
            current->children[i] = new TrieNode();
        } 
        current = current->children[i]; // atualiza o ponteiro auxiliar para o filho correspondente (caminha pela árvore)
    }
    if (current->isEndOfTitle) { 
            return false; // Jogo já existe, recusa a inserção
    }

    // Ao final atualiza os atributos indicando que a TrieNode ao final 
    // corresponde a um jogo 
    current->isEndOfTitle = true;
    current->game = game;

    return true; // retorna true se a inserção ocorreu deviddamente
}

// Método para verificar existe um dado jogo na Trie pelo seu título
bool Trie::contains(std::string title){
    title = this->toSearchKey(title); // converte a string para o padrão da Trie

    TrieNode* current = root;

    for(char c : title){
        // Calcula o índice correspondente ao caractere
        int i;
        if(c >= 97 && c <= 122){
            i = c - 97;
        } else if (c >= 48 && c <= 57) { 
            i = c - 22;
        } else {
            continue; 
        }

        // Se o filho correspondente a algum caracter numa ordem específica
        // não existir significa que o titulo não está na Trie e retorna false
        if(current->children[i] == nullptr){ 
            return false;
        } 
        current = current->children[i];
    }
    // Após passar pelas fases anteriores, verifica se um jogo já foi inserido anteriormente na TrieNode que é obtida ao final
    return current->isEndOfTitle; 
}

// Método para ordenar um vetor de Game*
// Usa o algoritmo de InsertionSort
// Ordena por popularidade e, em caso de empate, por ordem alfabética
void Trie::sortResults(std::vector<Game*>& games){
    // Obtém o tamanho do vetor e declara variáveis auxiliares
    int n = games.size(); 
    int i, j;                        
    Game* current;

    // Percorre o vetor a partir do segundo elemento
    for (i = 1; i < n; i++) {                  
        current = games[i];    // elemento atual a ser posicionado corretamente           
        j = i - 1;                          

        while (j >= 0){   
            bool swapGames = false;

            // Critério 1: Maior popularidade
            if(games[j]->getPopularity() < current->getPopularity()){
                swapGames = true;
            }
            // Critério 2: em caso de empate em popularidade ordena então por ordem alfabética
            else if (games[j]->getPopularity() == current->getPopularity()){
                string title_current = this->toSearchKey(current->getTitle());
                string title_j = this->toSearchKey(games[j]->getTitle());

                // Se o título anterior for "maior" em ordem alfabética, deve trocar
                if(title_j > title_current){
                    swapGames = true;
                }
            }

            // Se precisa trocar, desloca o elemento para a direita
            if(swapGames){
                games[j+1] = games[j];                
                j = j - 1;    
            } else {
                break; // posição correta encontrada
            }
        }
        // Insere o elemento atual na posição correta
        games[j+1] = current;                    
    }
}

// Método auxiliar para percorrer a Trie e coletar jogos a partir de um nó específico
void Trie::find_games(std::vector<Game*>& games, TrieNode* node){
    // Se o nó for nulo, nada a se fazer
    if(node == nullptr){
        return;
    }

    // Se o nó representa um título de Game, armazena o jogo no vetor
    if(node->isEndOfTitle){
        games.push_back(node->game);
    }

    // Percorre todos os filhos existentes por recursão
    for(int i = 0; i<36; i++){
        if (node->children[i] != nullptr) {
            this->find_games(games, node->children[i]);
        }
    }
}

// Método de autocompletar títulos de jogos com base num dado prefixo
// Retorna até k jogos compatíveis
std::vector<Game*> Trie::autocomplete(std::string prefix, int k){
    std::vector<Game*> games; // Declara o vetor para armazenar os resultados

    // Se k for inválido, retorna o vetor vazio
    if(k<=0){
        return games;
    }

    // Converte o prefixo para o formato padrão da Trie
    prefix = this->toSearchKey(prefix);

    TrieNode* current = root;

    // Percorre a Trie seguindo o caminho do prefixo
    for(char c : prefix){
        int i;
        // Calcula o índice correspondente ao caractere
        if(c >= 97 && c <= 122){
            i = c - 97;
        } else if (c >= 48 && c <= 57) { 
            i = c - 22;
        } else {
            continue; 
        }

        // Se em algum momento não encontrar nó correspondente, não há games com esse prefixo
        if (current->children[i] == nullptr) {
            return games;
        }

        current = current->children[i];  // avança na Trie
    }

    // Coleta os jogos a partir do nó específico e ordena o vetor de jogos
    this->find_games(games, current);
    this->sortResults(games);

    // Se obter mais que k jogos, mantém apenas os k primeiros da ordenação
    if (games.size() > k) {
        games.resize(k);
    }

    return games; 
}