#pragma once
#include "Piece.h"

class Queen : public Piece{
    //Construtor
    Queen(Color pieceColor) : Piece(pieceColor){}

    //Movimento
    bool isValidMove(Position fromPosition, Position toPosition) const override;
};