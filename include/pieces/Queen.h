#pragma once
#include "Piece.h"

class Queen : public Piece{
    public:
        //Construtor
        Queen(Color pieceColor) : Piece(pieceColor){}

        //Movimento
        bool isValidMove(const Move &move, const Board &board) const override;

        //Metodo para obter o tipo de peça
        PieceType getType() const override { return PieceType::Queen; }
};