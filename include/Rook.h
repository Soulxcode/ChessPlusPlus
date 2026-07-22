#pragma once
#include "Piece.h"

class Rook : public Piece{
    //Construtor
    Rook(Color pieceColor) : Piece(pieceColor){}

    //Movimento
    bool isValidMove(Position fromPosition, Position toPosition) const override;
};