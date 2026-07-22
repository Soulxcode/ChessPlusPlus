#pragma once
#include "Piece.h"
#include "Position.h"

class Knight : public Piece {
    public:
        //Construtor
        Knight(Color pieceColor, Position initialPosition);

        //Movimento
        bool isValidMove(const Move &move, const Board &board) const override;
};