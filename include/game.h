#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "ui/Renderer.h"

class Game
{
    public:
        //Construtor
        Game();

        //Metodo que abre a aaplicação
        void run();

    private:

        //Metodo para processar eventos
        void processEvents();

        //Metodo para atualizar a screen
        void update();

        //Metodo para renderizar o jogo
        void render();

        sf::RenderWindow window;

        Board board;
        Renderer renderer;
};