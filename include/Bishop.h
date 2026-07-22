#pragma once
#include "Piece.h"

class Bishop : public Piece{
    //Construtor
    Bishop(Color pieceColor) : Piece(pieceColor){}

    //Movimento
    bool isValidMove(Position fromPosition, Position toPosition) const override;

};