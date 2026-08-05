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

        //Metodo que altera o turno
        void switchTurn();

        //Faz render de uma janela
        sf::RenderWindow window;

        //Cria um tabuleiro para jogar
        Board board;

        //Criar um renderer para renderizar as imagens
        Renderer renderer;

        //Bool para verificar se há alguma peça selecionada
        bool selected = false;

        //Para guardar a posição selecionada
        Position selectedPosition{0, 0};
        
        //Turno inicial é sempre branco
        Color currentTurn = Color::White;
};