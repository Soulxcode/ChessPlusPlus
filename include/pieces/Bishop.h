#pragma once
#include "Piece.h"

class Bishop : public Piece{
    public:
        //Construtor
        Bishop(Color pieceColor) : Piece(pieceColor){}

        //Movimento
        bool isValidMove(const Move &move, const Board &board) const override;
};