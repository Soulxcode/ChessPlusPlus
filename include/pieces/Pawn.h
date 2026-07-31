#pragma once
#include "Piece.h"

class Pawn : public Piece {
    public:
        //Construtor
        Pawn(Color pieceColor) : Piece(pieceColor){}

        //Movimento do peão
        bool isValidMove(const Move &move, const Board &board) const override;

        //Metodo para obter o tipo de peça
        PieceType getType() const override { return PieceType::Pawn; }

    private:
        //Controla se o peao ja se moveu    
        bool hasMoved = false;
};