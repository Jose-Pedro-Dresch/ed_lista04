#ifndef GAME_HPP
#define GAME_HPP

#include <string>

/**
    * Classe representando um jogo do sistema, 
    * com título, descrição e popularidade
*/
class Game {
private:
    std::string title;
    std::string shortDescription;
    int popularity;

public:
    /**
        * Construtor padrão sem parâmetros da classe Game.
    */
    Game();

    /**
        * Construtor com parâmetros de Game, com
        * título, descrição e popularidade
    */
    Game(std::string title, std::string shortDescription, int popularity);

    /**
        * Destrutor de Game;
    */
    ~Game();

    // Getters para os atributos de Game
    std::string getTitle();
    std::string getShortDescription();
    int getPopularity();
};

#endif