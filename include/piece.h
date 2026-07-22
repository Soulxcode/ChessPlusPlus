#pragma once
#include "Color.h"

//Todos os tipos das pecas
class Piece
{
    public:
        //Destructor é usado automaticamente
        virtual ~Piece() = default;

        //Verifica se o movimento é válido
        virtual bool isValidMove(Position fromPosition, Position toPosition) const = 0;

        //Devolve a cor da peça
        virtual Color getColor() const = 0;
    
    protected:
        //Construtor  
        Piece(Color pieceColor) : color(pieceColor){}

    private:
        //Cor da peça
        Color color;
};

