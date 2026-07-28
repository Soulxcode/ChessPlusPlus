#include "ui/Renderer.h"
#include <iostream>

//Tamanho de cada quadrado
const int TILE_SIZE = 80;

//Construtor
Renderer::Renderer()
{
    //Tenta carregar imagens para os quadrados
    if (!lightSquareTexture.loadFromFile("assets/png/noShadow/128px/square_brown_light_png_128px.png"))
    {
        std::cerr << "Falha ao carregar quadrado branco" << std::endl;
    }

    if (!darkSquareTexture.loadFromFile("assets/png/noShadow/128px/square_brown_dark_png_128px.png"))
    {
        std::cerr << "Falha ao carregar quadrado preto" << std::endl;
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