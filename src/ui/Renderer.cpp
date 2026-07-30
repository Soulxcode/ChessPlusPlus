#include "ui/Renderer.h"
#include "Position.h"
#include "Board.h"
#include "Constants.h"
#include <iostream>

//Construtor
Renderer::Renderer()
{
    //Carrega imagens para os quadrados
    if (!boardTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/blue.png"))
    {
        std::cerr << "Falha ao carregar tabuleiro" << std::endl;
    }
    //Carrega imagens para as peças
    if (!darkBishopTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bb.png"))
    {
        std::cerr << "Falha ao carregar bispo preto" << std::endl;
    }
    if (!lightBishopTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wb.png"))
    {
        std::cerr << "Falha ao carregar bispo branco" << std::endl;
    }

    if (!darkKingTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bk.png"))
    {
        std::cerr << "Falha ao carregar rei preto" << std::endl;
    }
    if (!lightKingTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wk.png"))
    {
        std::cerr << "Falha ao carregar rei branco" << std::endl;
    }

    if (!darkKnightTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bn.png"))
    {
        std::cerr << "Falha ao carregar cavalo preto" << std::endl;
    }
    if (!lightKnightTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wn.png"))
    {
        std::cerr << "Falha ao carregar cavalo branco" << std::endl;
    }

    if (!darkQueenTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bq.png"))
    {
        std::cerr << "Falha ao carregar rainha preta" << std::endl;
    }
    if (!lightQueenTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wq.png"))
    {
        std::cerr << "Falha ao carregar rainha branca" << std::endl;
    }

    if (!darkPawnTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bp.png"))
    {
        std::cerr << "Falha ao carregar peão preto" << std::endl;
    }
    if (!lightPawnTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wp.png"))
    {
        std::cerr << "Falha ao carregar peão branco" << std::endl;
    }

    if (!darkRookTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/br.png"))
    {
        std::cerr << "Falha ao carregar torre preta" << std::endl;
    }
    if (!lightRookTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wr.png"))
    {
        std::cerr << "Falha ao carregar torre branca" << std::endl;
    }
}

void Renderer::drawBoard(sf::RenderWindow& window){
        sf::Sprite boardSprite(boardTexture);
        boardSprite.setPosition(sf::Vector2f(0.f, 0.f));
        window.draw(boardSprite);
}

void Renderer::drawCenteredPiece(sf::RenderWindow& window, const sf::Texture& texture, const Position& position){

    //Criar uma sprite com a textura recebida
    sf::Sprite sprite(texture);

    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
    sf::Vector2u size = texture.getSize();
    float offsetX = (TILE_SIZE - static_cast<float>(size.x)) / 2.f;
    float offsetY = (TILE_SIZE - static_cast<float>(size.y)) / 2.f;

    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
    sprite.setPosition({ position.getCol() * TILE_SIZE + offsetX , position.getRow() * TILE_SIZE + offsetY });

    //Desenha a peça
    window.draw(sprite);
}

void Renderer::drawPieces(sf::RenderWindow& window, const Board& board){
    for(int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            
            //Fica com a posição e ve que tipo de peça está lá
            Position position(row, col);
            Piece* piece = board.getPiece(position);
            
            //Se nenhuma peça, continua o loop
            if(piece == nullptr){
                continue;
            }
            
            //Verifica o tipo da peça para inserir a textura correta na posição correta
            PieceType type = piece -> getType();
            
            switch(type){
                case PieceType::Pawn:
                {
                    drawCenteredPiece(window, piece->getColor() == Color::White ? lightPawnTexture : darkPawnTexture, position);
                    break;
                }        
                case PieceType::Bishop:
                {
                    drawCenteredPiece(window, piece->getColor() == Color::White ? lightBishopTexture : darkBishopTexture, position);
                    break;
                }
                case PieceType::King:
                {
                    drawCenteredPiece(window, piece->getColor() == Color::White ? lightKingTexture : darkKingTexture, position);
                    break;
                }    
                case PieceType::Knight:
                {
                    drawCenteredPiece(window, piece->getColor() == Color::White ? lightKnightTexture : darkKnightTexture, position);
                    break;
                }
                case PieceType::Queen:
                {
                    drawCenteredPiece(window, piece->getColor() == Color::White ? lightQueenTexture : darkQueenTexture, position);
                    break;
                }            
                case PieceType::Rook:
                {
                    drawCenteredPiece(window, piece->getColor() == Color::White ? lightRookTexture : darkRookTexture, position);
                    break;
                }      
            }
        }
    }
}

