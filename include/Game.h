#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "ui/Renderer.h"

class Game 
{
    public:
        //Construtor
        Game();

        //Metodo que abre a aplicação
        void run();

    private:

        //Metodo para processar eventos
        void processEvents();

        //Metodo para atualizar a screen
        void update();

        //Metodo para renderizar o jogo
        void render();

        //Metodo para o click do lado esquerdo do rato
        void leftClick(sf::Vector2i mousePosition);

        //Faz render de uma janela
        sf::RenderWindow window;

        //Cria um tabuleiro para jogar
        Board board;

        //Criar um renderer para renderizar as imagens
        Renderer renderer;
};