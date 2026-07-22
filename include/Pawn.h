#pragma once
#include "Piece.h"
#include "Position.h"

class Pawn : public Piece {
    public:
        //Construtor
        Pawn(Color pieceColor) : Piece(pieceColor){}

        //Movimento
        bool isValidMove(Position fromPosition, Position toPosition) const override;
};