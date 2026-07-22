#pragma once
#include "Piece.h"

class Rook : public Piece{
    public:
        //Construtor
        Rook(Color pieceColor) : Piece(pieceColor){}

        //Movimento
        bool isValidMove(const Move &move, const Board &board) const override;
};