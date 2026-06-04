#include "Game.hpp"

// Construtor sem parâmetros de Game
Game::Game(){
}

// Construtor com parâmetros de Game
Game::Game(std::string title, std::string shortDescription, int popularity) {
    this->title = title;
    this->shortDescription = shortDescription;
    this->popularity = popularity;
}

// Destrutor de Game
Game::~Game() {}

// Getters para os atributos de Game
std::string Game::getTitle() { return title; }
std::string Game::getShortDescription() { return shortDescription; }
int Game::getPopularity() { return popularity; }