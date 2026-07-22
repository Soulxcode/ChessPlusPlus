#pragma once
#include "Piece.h"
#include "Position.h"

class Knight : public Piece {
    public:
        //Construtor
        Knight(Color pieceColor, Position initialPosition);

        //Movimento
        bool isValidMove(Position fromPosition, Position toPosition) const override;
};