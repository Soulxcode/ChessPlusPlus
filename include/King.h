#pragma once
#include "Piece.h"

class King : public Piece{
    public:
        //Construtor
        King(Color pieceColor) : Piece(pieceColor){}

        //Movimentos
        bool isValidMove(Position fromPosition, Position toPosition) const override;
};