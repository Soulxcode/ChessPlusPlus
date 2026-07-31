#pragma once
#include "Piece.h"
#include "Move.h"

class King : public Piece{
    public:
        //Construtor
        King(Color pieceColor) : Piece(pieceColor){}

        //Movimento do rei
        bool isValidMove(const Move &move, const Board &board) const override;

        //Metodo para obter o tipo de peça
        PieceType getType() const override { return PieceType::King; }
};