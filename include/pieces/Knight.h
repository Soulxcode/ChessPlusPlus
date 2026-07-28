#pragma once
#include "Piece.h"

class Knight : public Piece {
    public:
        //Construtor
        Knight(Color pieceColor) : Piece(pieceColor){}

        //Movimento
        bool isValidMove(const Move &move, const Board &board) const override;
};