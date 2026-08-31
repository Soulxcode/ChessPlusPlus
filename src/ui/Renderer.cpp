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
    if (!font.openFromFile("assets/font/Cinzel.ttf"))
    {
        std::cout << "Falha ao carregar fonte" << std::endl;
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

void Renderer::drawMoveHints(sf::RenderWindow& window, const std::vector<Position>& validMoves, const Board& board){
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

void Renderer::drawGameOver(sf::RenderWindow& window, const std::string& message){
    
    //Cria o texto
    sf::Text gameOverText(font);

    //Parâmetros do texto
    gameOverText.setString(message);
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color(218, 165, 32));
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(3.0f);

    //Espaço que o texto ocupa
    sf::FloatRect bounds = gameOverText.getLocalBounds();

    //Mete o texto no meio do seu espaço
    gameOverText.setOrigin({
        bounds.position.x + bounds.size.x / 2.0f, 
        bounds.position.y + bounds.size.y / 2.0f 
        });
    
    //Mete o texto no meio do ecra
    gameOverText.setPosition({ WIDTH / 2.0f, HEIGHT / 2.0f });

    window.draw(gameOverText);
}

void Renderer::drawPromotionOptions(sf::RenderWindow& window, Position position, Color color)
{
    //Direção para desenhar as opções, se a promoção é na linha 0, desenha para baixo; se é na linha 7, desenha para cima
    int direction = (position.getRow() == 0) ? DOWN : UP;

    //As 4 texturas a mostrar, na ordem: Queen, Rook, Bishop, Knight
    const sf::Texture* options[4];

    //Guarda as texturas num array dependendo de quem esta a promover
    if (color == Color::White)
    {
        options[0] = &lightQueenTexture;
        options[1] = &lightRookTexture;
        options[2] = &lightBishopTexture;
        options[3] = &lightKnightTexture;
    }
    else
    {
        options[0] = &darkQueenTexture;
        options[1] = &darkRookTexture;
        options[2] = &darkBishopTexture;
        options[3] = &darkKnightTexture;
    }

    for (int i = 0; i < 4; i++)
    {
        int row = position.getRow() + (i * direction);
        int col = position.getCol();

        //Desenha um fundo para destacar a opção
        sf::RectangleShape background(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        background.setPosition(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
        background.setFillColor(sf::Color(200, 200, 200, 230));
        window.draw(background);

        //Desenha opçao
        sf::Sprite optionSprite(*options[i]);
        optionSprite.setPosition(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
        window.draw(optionSprite);
    }
}

void Renderer::drawRematchButton(sf::RenderWindow& window)
{
    float buttonWidth = 200.f;
    float buttonHeight = 60.f;

    //Centrar horizontalmente e um pouco abaixo do centro
    float x = (WIDTH - buttonWidth) / 2.f;
    float y = (HEIGHT - buttonHeight) / 2.f + 100.f;

    rematchButtonBounds = sf::FloatRect({x, y}, {buttonWidth, buttonHeight});

    sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
    button.setPosition(sf::Vector2f(x, y));
    button.setFillColor(sf::Color::Black);
    //button.setFillColor(sf::Color(70, 130, 180));

    sf::Text text(font, "Rematch", 30);
    text.setFillColor(sf::Color::White);

    //Centraliza o texto dentro do botão
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(sf::Vector2f(
        x + (buttonWidth - textBounds.size.x) / 2.f,
        y + (buttonHeight - textBounds.size.y) / 2.f - textBounds.position.y
    ));

    window.draw(button);
    window.draw(text);
}

bool Renderer::isRematchButtonClicked(sf::Vector2i mousePosition) const
{
    return rematchButtonBounds.contains(sf::Vector2f(mousePosition));
}