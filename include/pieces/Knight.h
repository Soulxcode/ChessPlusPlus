#pragma once
#include "Piece.h"

class Knight : public Piece {
    public:
        //Construtor
        Knight(Color pieceColor) : Piece(pieceColor){}

        //Movimento do cavaleiro
        bool isValidMove(const Move &move, const Board &board) const override;

        //Metodo para obter o tipo de peça
        PieceType getType() const override { return PieceType::Knight; }
};