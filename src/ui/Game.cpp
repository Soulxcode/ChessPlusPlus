#include "ui/Game.h"

Game::Game() : window(sf::VideoMode(sf::Vector2u(640, 640)), "Chess++"){}

void Game::run()
{
    while (window.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents(){

    //Verifica se aconteceu algum evento
    while (const std::optional event = window.pollEvent()){
        
        //Verifica se o evento é fechar a janela do jogo
        //Se sim, fecha a janela
        if (event->is<sf::Event::Closed>()){
            window.close();
        }
    }
}

void Game::update(){
    //TODO: LOGICA DO JOGO
}

void Game::render()
{
    window.clear();
    renderer.drawBoard(window);
    window.display();
}