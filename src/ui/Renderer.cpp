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
        std::cout << "Falha ao carregar tabuleiro" << std::endl;
    }
    //Carrega imagens para as peças
    if (!darkBishopTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bb.png"))
    {
        std::cout << "Falha ao carregar bispo preto" << std::endl;
    }
    if (!lightBishopTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wb.png"))
    {
        std::cout << "Falha ao carregar bispo branco" << std::endl;
    }
    if (!darkKingTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bk.png"))
    {
        std::cout << "Falha ao carregar rei preto" << std::endl;
    }
    if (!lightKingTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wk.png"))
    {
        std::cout << "Falha ao carregar rei branco" << std::endl;
    }
    if (!darkKnightTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bn.png"))
    {
        std::cout << "Falha ao carregar cavalo preto" << std::endl;
    }
    if (!lightKnightTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wn.png"))
    {
        std::cout << "Falha ao carregar cavalo branco" << std::endl;
    }
    if (!darkQueenTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bq.png"))
    {
        std::cout << "Falha ao carregar rainha preta" << std::endl;
    }
    if (!lightQueenTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wq.png"))
    {
        std::cout << "Falha ao carregar rainha branca" << std::endl;
    }
    if (!darkPawnTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/bp.png"))
    {
        std::cout << "Falha ao carregar peão preto" << std::endl;
    }
    if (!lightPawnTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wp.png"))
    {
        std::cout << "Falha ao carregar peão branco" << std::endl;
    }
    if (!darkRookTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/br.png"))
    {
        std::cout << "Falha ao carregar torre preta" << std::endl;
    }
    if (!lightRookTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/wr.png"))
    {
        std::cout << "Falha ao carregar torre branca" << std::endl;
    }
    if (!errorSquare.loadFromFile("assets/boardsPieces/pieces/pieces-png/redSquare.png"))
    {
        std::cout << "Falha ao carregar imagem de erro" << std::endl;
    }
    if (!highlightTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/greenSquare.png"))
    {
        std::cout << "Falha ao carregar imagem highlight" << std::endl;
    }
    if (!moveTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/move_dot.png"))
    {
        std::cout << "Falha ao carregar imagem do move" << std::endl;
    }
    if (!captureTexture.loadFromFile("assets/boardsPieces/pieces/pieces-png/capture_ring.png"))
    {
        std::cout << "Falha ao carregar imagem de captura" << std::endl;
    }
}

void Renderer::drawBoard(sf::RenderWindow& window){
        
    //Desenha o board no meio do ecra
    sf::Sprite boardSprite(boardTexture);
    boardSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
    window.draw(boardSprite);
}

void Renderer::drawCenteredPiece(sf::RenderWindow& window, const sf::Texture& texture, const Position& position){

    //Criar uma sprite com a textura recebida
    sf::Sprite sprite(texture);

    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
    sf::Vector2u size = texture.getSize();
    float offsetX = (TILE_SIZE - static_cast<float>(size.x)) / 2.0f;
    float offsetY = (TILE_SIZE - static_cast<float>(size.y)) / 2.0f;

    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
    sprite.setPosition({ position.getCol() * TILE_SIZE + offsetX , position.getRow() * TILE_SIZE + offsetY });

    //Desenha a peça
    window.draw(sprite);
}

void Renderer::drawPieces(sf::RenderWindow& window, const Board& board){
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            
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

void Renderer::drawHighlight(sf::RenderWindow& window, const Position& position, bool isActive){
    
    //Se nao esta ativo nada para desenhar
    if(!isActive){
        return;
    }

    //Se ativo, desenha o highlight
    sf::Sprite highlight(highlightTexture);
    highlight.setPosition(sf::Vector2f(position.getCol() * TILE_SIZE, position.getRow() * TILE_SIZE));
    window.draw(highlight);
}

void Renderer::drawMoveHints(sf::RenderWindow& window, const std::vector<Position>& validMoves, const Board& board)
{
    for (const Position& pos : validMoves)
    {
        //Verifica se é uma captura
        bool isCapture = board.getPiece(pos) != nullptr;
        
        //Desenha a sprite dependendo se é captura ou movimento
        sf::Sprite hint(isCapture ? captureTexture : moveTexture);
        hint.setPosition(sf::Vector2f(pos.getCol() * TILE_SIZE, pos.getRow() * TILE_SIZE));
        window.draw(hint);
    }
}
