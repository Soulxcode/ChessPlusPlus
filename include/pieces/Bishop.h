#pragma once
#include "Piece.h"

class Bishop : public Piece{
    public:
        //Construtor
        Bishop(Color pieceColor) : Piece(pieceColor){}

        //Movimento
        bool isValidMove(const Move &move, const Board &board) const override;

        //Metodo para obter o tipo de peça
        PieceType getType() const override { return PieceType::Bishop; }
};