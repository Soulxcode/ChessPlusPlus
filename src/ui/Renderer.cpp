#include "ui/Renderer.h"

//Construtor
Renderer::Renderer(){}

//Metodo que desenha o tabuleiro
void drawBoard(sf::RenderWindow& window){
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col ++){

            //Verifica se é par para saber que png colocar
            bool isLight = (row + col) % 2 == 0;

            if(isLight){
                
            }


        }
    }
}