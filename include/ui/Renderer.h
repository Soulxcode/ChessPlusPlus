#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Renderer{
    public:
        //Construtor
        Renderer();
        
        //Metodo que desenha o tabuleiro
        void drawBoard(sf::RenderWindow& window);

        //Metodo para centrar as peças no quadrado
        void drawCenteredPiece(sf::RenderWindow& window, const sf::Texture& texture, const Position& position);

        //Metodo que desenha as peças 
        void drawPieces(sf::RenderWindow& window, const Board& board);

    private:
        //Texturas do board e peças
        sf::Texture boardTexture;
        sf::Texture lightBishopTexture;
        sf::Texture darkBishopTexture;
        sf::Texture lightRookTexture;
        sf::Texture darkRookTexture;
        sf::Texture lightPawnTexture;
        sf::Texture darkPawnTexture;
        sf::Texture lightQueenTexture;
        sf::Texture darkQueenTexture;
        sf::Texture lightKingTexture;
        sf::Texture darkKingTexture;
        sf::Texture lightKnightTexture;
        sf::Texture darkKnightTexture;

};