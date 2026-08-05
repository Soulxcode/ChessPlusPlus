#pragma once
#include "Color.h"
#include <string>

class Player{
    private:
        //Cor das pecas do jogador
        Color color;

        //Nome do jogador
        std::string name;

    public:
        //Construtor
        Player(std::string nome, Color color);

        //Vai buscar a cor do jogador
        Color getColor() const; 
};