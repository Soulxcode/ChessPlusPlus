#pragma once
#include "Piece.h"
#include "Move.h"

class King : public Piece{
    public:
        //Construtor
        King(Color pieceColor) : Piece(pieceColor){}

        //Movimentos
        bool isValidMove(const Move &move, const Board &board) const override;
};