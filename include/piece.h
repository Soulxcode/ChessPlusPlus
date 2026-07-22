#pragma once
#include "Color.h"
#include "Move.h"

//Todos os tipos das pecas
class Piece
{
    public:
        //Destructor é usado automaticamente
        virtual ~Piece() = default;

        //Verifica se o movimento é válido
        virtual bool isValidMove(const Move &move, const Board &board) const = 0;

        //Devolve a cor da peça
        Color getColor(){
            return color;
        };
    
    protected:
        //Construtor  
        Piece(Color pieceColor) : color(pieceColor){}

    private:
        //Cor da peça
        Color color;
};

