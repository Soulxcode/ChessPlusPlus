#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Renderer{
    public:
        //Construtor
        Renderer();
        
        //Metodo que desenha o tabuleiro
        void drawBoard(sf::RenderWindow& window);

        //Metodo que desenha as peças 
        void drawPieces(sf::RenderWindow& window, const Board& board);

    private:
        //Textura peças
        sf::Texture piecesTexture;

        //Textura do board
        sf::Texture boardTexture;
};