#include "ui/Renderer.h"
#include "Position.h"
#include "Board.h"
#include <iostream>

//Tamanho de cada quadrado
const int TILE_SIZE = 128;

//Construtor
Renderer::Renderer()
{
    //Carrega imagens para os quadrados
    if (!lightSquareTexture.loadFromFile("assets/PNGs/noShadow/128h/square_brown_light_png_128px.png"))
    {
        std::cerr << "Falha ao carregar quadrado claro" << std::endl;
    }
    if (!darkSquareTexture.loadFromFile("assets/PNGs/noShadow/128h/square_brown_dark_png_128px.png"))
    {
        std::cerr << "Falha ao carregar quadrado escuro" << std::endl;
    }

    //Carrega imagens para as peças
    if (!darkBishopTexture.loadFromFile("assets/PNGs/noShadow/128h/b_bishop_png_128px.png"))
    {
        std::cerr << "Falha ao carregar bispo preto" << std::endl;
    }
    if (!lightBishopTexture.loadFromFile("assets/PNGs/noShadow/128h/w_bishop_png_128px.png"))
    {
        std::cerr << "Falha ao carregar bispo branco" << std::endl;
    }

    if (!darkKingTexture.loadFromFile("assets/PNGs/noShadow/128h/b_king_png_128px.png"))
    {
        std::cerr << "Falha ao carregar rei preto" << std::endl;
    }
    if (!lightKingTexture.loadFromFile("assets/PNGs/noShadow/128h/w_king_png_128px.png"))
    {
        std::cerr << "Falha ao carregar rei branco" << std::endl;
    }

    if (!darkKnightTexture.loadFromFile("assets/PNGs/noShadow/128h/b_knight_png_128px.png"))
    {
        std::cerr << "Falha ao carregar cavalo preto" << std::endl;
    }
    if (!lightKnightTexture.loadFromFile("assets/PNGs/noShadow/128h/w_knight_png_128px.png"))
    {
        std::cerr << "Falha ao carregar cavalo branco" << std::endl;
    }

    if (!darkQueenTexture.loadFromFile("assets/PNGs/noShadow/128h/b_queen_png_128px.png"))
    {
        std::cerr << "Falha ao carregar rainha preta" << std::endl;
    }
    if (!lightQueenTexture.loadFromFile("assets/PNGs/noShadow/128h/w_queen_png_128px.png"))
    {
        std::cerr << "Falha ao carregar rainha branca" << std::endl;
    }

    if (!darkPawnTexture.loadFromFile("assets/PNGs/noShadow/128h/b_pawn_png_128px.png"))
    {
        std::cerr << "Falha ao carregar peão preto" << std::endl;
    }
    if (!lightPawnTexture.loadFromFile("assets/PNGs/noShadow/128h/w_pawn_png_128px.png"))
    {
        std::cerr << "Falha ao carregar peão branco" << std::endl;
    }

    if (!darkRookTexture.loadFromFile("assets/PNGs/noShadow/128h/b_rook_png_128px.png"))
    {
        std::cerr << "Falha ao carregar torre preta" << std::endl;
    }
    if (!lightRookTexture.loadFromFile("assets/PNGs/noShadow/128h/w_rook_png_128px.png"))
    {
        std::cerr << "Falha ao carregar torre branca" << std::endl;
    }
}

//Metodo que desenha o tabuleiro
void Renderer::drawBoard(sf::RenderWindow& window){
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col ++){

            //Verifica se é par para saber se é um quadrado branco ou preto
            bool isLight = (row + col) % 2 == 0;
            sf::Sprite square(isLight ? lightSquareTexture : darkSquareTexture);
            
            //Converte col e row em coordenadas
            //x - col; y - row
            square.setPosition(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
            
            //Pede á janela para desenhar o quadrado
            window.draw(square);
        }
    }
}

void Renderer::drawPieces(sf::RenderWindow& window, const Board &board){
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
                    //Usa referencia para ficar com a textura correta da peça sem criar uma copia
                    const sf::Texture& pawnTexture = (piece->getColor() == Color::White) ? lightPawnTexture : darkPawnTexture;
                    sf::Sprite pieceSprite(pawnTexture);

                    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
                    sf::Vector2u textureSize = pawnTexture.getSize();
                    float offsetX = (TILE_SIZE - static_cast<float>(textureSize.x)) / 2.0f;
                    float offsetY = (TILE_SIZE - static_cast<float>(textureSize.y)) / 2.0f;

                    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
                    pieceSprite.setPosition(sf::Vector2f(col * TILE_SIZE + offsetX, row * TILE_SIZE + offsetY));
                    window.draw(pieceSprite);
                    break;
                }        
                case PieceType::Bishop:
                {
                    //Usa referencia para ficar com a textura correta da peça sem criar uma copia
                    const sf::Texture& bishopTexture = (piece->getColor() == Color::White) ? lightBishopTexture : darkBishopTexture;
                    sf::Sprite pieceSprite(bishopTexture);

                    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
                    sf::Vector2u textureSize = bishopTexture.getSize();
                    float offsetX = (TILE_SIZE - static_cast<float>(textureSize.x)) / 2.0f;
                    float offsetY = (TILE_SIZE - static_cast<float>(textureSize.y)) / 2.0f;

                    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
                    pieceSprite.setPosition(sf::Vector2f(col * TILE_SIZE + offsetX, row * TILE_SIZE + offsetY));
                    window.draw(pieceSprite);
                    break;
                }
                case PieceType::King:
                {
                    //Usa referencia para ficar com a textura correta da peça sem criar uma copia
                    const sf::Texture& kingTexture = (piece->getColor() == Color::White) ? lightKingTexture : darkKingTexture;
                    sf::Sprite pieceSprite(kingTexture);

                    //Fica com o tamanho da textura da peça, largura e comprimento
                    sf::Vector2u textureSize = kingTexture.getSize();
                    float offsetX = (TILE_SIZE - static_cast<float>(textureSize.x)) / 2.0f;
                    float offsetY = (TILE_SIZE - static_cast<float>(textureSize.y)) / 2.0f;

                    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
                    pieceSprite.setPosition(sf::Vector2f(col * TILE_SIZE + offsetX, row * TILE_SIZE + offsetY));
                    window.draw(pieceSprite);
                    break;
                }    
                case PieceType::Knight:
                {
                    //Usa referencia para ficar com a textura correta da peça sem criar uma copia
                    const sf::Texture& knightTexture = (piece->getColor() == Color::White) ? lightKnightTexture : darkKnightTexture;
                    sf::Sprite pieceSprite(knightTexture);

                    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
                    sf::Vector2u textureSize = knightTexture.getSize();
                    float offsetX = (TILE_SIZE - static_cast<float>(textureSize.x)) / 2.0f;
                    float offsetY = (TILE_SIZE - static_cast<float>(textureSize.y)) / 2.0f;

                    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
                    pieceSprite.setPosition(sf::Vector2f(col * TILE_SIZE + offsetX, row * TILE_SIZE + offsetY));
                    window.draw(pieceSprite);
                    break;
                }
                case PieceType::Queen:
                {
                    //Usa referencia para ficar com a textura correta da peça sem criar uma copia
                    const sf::Texture& queenTexture = (piece->getColor() == Color::White) ? lightQueenTexture : darkQueenTexture;
                    sf::Sprite pieceSprite(queenTexture);

                    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
                    sf::Vector2u textureSize = queenTexture.getSize();
                    float offsetX = (TILE_SIZE - static_cast<float>(textureSize.x)) / 2.0f;
                    float offsetY = (TILE_SIZE - static_cast<float>(textureSize.y)) / 2.0f;

                    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
                    pieceSprite.setPosition(sf::Vector2f(col * TILE_SIZE + offsetX, row * TILE_SIZE + offsetY));
                    window.draw(pieceSprite);
                    break;
                }            
                case PieceType::Rook:
                {
                    //Usa referencia para ficar com a textura correta da peça sem criar uma copia
                    const sf::Texture& rookTexture = (piece->getColor() == Color::White) ? lightRookTexture : darkRookTexture;
                    sf::Sprite pieceSprite(rookTexture);

                    //Fica com o tamanho da textura da peça, faz cast para float da largura e comprimento
                    sf::Vector2u textureSize = rookTexture.getSize();
                    float offsetX = (TILE_SIZE - static_cast<float>(textureSize.x)) / 2.0f;
                    float offsetY = (TILE_SIZE - static_cast<float>(textureSize.y)) / 2.0f;

                    //Usa largura e o comprimento para centrar a peça no seu quadrado do tabuleiro
                    pieceSprite.setPosition(sf::Vector2f(col * TILE_SIZE + offsetX, row * TILE_SIZE + offsetY));
                    window.draw(pieceSprite);
                    break;
                }      
            }
        }
    }
}

