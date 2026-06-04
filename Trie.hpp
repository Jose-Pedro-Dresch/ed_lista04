#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include "Game.hpp"

// constante representando os caracteres válidos na chave de busca
const int ALPHABET_SIZE = 36;  // 26 letras + 10 algarismos


//=====================================================================================================================
//                                                  Classe TrieNode
//=====================================================================================================================

/**
    * Classe representando um nó da Trie
    * Armazena uma lista de ponteiros para TrieNodes subsequentes,
    * um booleano indicando se esse nó representa um título de jogo específico
    * e o ponteiro para esse jogo caso isso ocorra
*/
class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    /**
        * Construtor sem parâmetros de TrieNode, 
        * inicializa a lista de filhos como nullptr, 
        * isEndOfTitle como false e game como nullptr
    */
    TrieNode();

    /**
        * Destrutor de TrieNode
        * Chama também os destrutores de cada filho
    */
    ~TrieNode();
};





//=====================================================================================================================
//                                                  Classe Trie 
//=====================================================================================================================


/**
    * Classe representando a Trie do sistema
    * É responsável por armazenar os jogos e
    * realizar as buscas por título e por prefixo.
    * Armazena um ponteiro para a TrieNode raiz.
*/
class Trie {
private:
    TrieNode* root;

public:
    /**
        * Construtor de uma Trie
        * Inicializa a TrieNode raiz
    */
    Trie();

    /**
        * Destrutor de uma Trie
        * Chama o destrutor da raíz, 
        * que por sua vez chama o destrutor dos filhos, 
        * e assim por diante
    */
    ~Trie();

    /**
        * Método para inserir um jogo na Trie usando o título do jogo
        *  como base para a chave de busca.
        * O parâmetro game é um ponteiro para um objeto Game 
        * já existente no array fornecido em GamesDatabase.cpp.
        * Caso a inserção seja realizada corretamente, o método retorna true.
    */
    bool insert(Game* game);

    /**
        * Método para verificar se existe um jogo com o título informado.
        * Retorna true caso o título seja encontrado e false caso contrário
    */
    bool contains(std::string title);

    /**
        * Método que retorna até k jogos cujo título começa com o prefixo informado
        * Caso nenhum jogo seja encontrado, o método retorna um vetor vazio.
        * Caso k <= 0, o método retorna um vetor vazio.
    */
    std::vector<Game*> autocomplete(std::string prefix, int k);

    /**
        * Método para converter um título ou prefixo 
        * para a forma utilizada internamente como chave na Trie.
    */
    std::string toSearchKey(std::string text);

    /**
        * Método auxiliar para ordenar o vetor recebido usando 
        * os critérios do autocomplete: maior popularidade e, 
        * em caso de empate, ordem alfabética.
    */
    void sortResults(std::vector<Game*>& games);

    /**
        * Método auxiliar criado para armazenar, por recursão, 
        * todos os jogos a partir de uma dada TrieNode, em um vetor 
        * de Game* dados.
    */
    void find_games(std::vector<Game*>& games, TrieNode* node);
};

#endif