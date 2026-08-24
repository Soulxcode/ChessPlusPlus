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

        //Metodo que desenha quadrado de erro
        void drawError(sf::RenderWindow& window, const Position& position);

        //Metodo que desenha highlight para peça escolhida
        void drawHighlight(sf::RenderWindow& window, const Position& position, bool isActive);

        //Metodo que desenha highlights das moves e capturas válidas 
        void drawMoveHints(sf::RenderWindow& window, const std::vector<Position>& validMoves, const Board& board);

        //Metodo que desenha texto de game over
        void drawGameOver(sf::RenderWindow& window, const std::string& message);

        //Metodo para desenhar opcoes de promoçao
        void drawPromotionOptions(sf::RenderWindow& window, Position position, Color color);

    private:
        //Texturas
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
        sf::Texture errorSquare;
        sf::Texture highlightTexture;
        sf::Texture moveTexture;
        sf::Texture captureTexture;

        //Texto
        sf::Font font;
};