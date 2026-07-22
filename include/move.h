#pragma once
#include "Piece.h"
#include "MoveType.h"

struct Move{
    Piece* piece;
    Position start;
    Position destination;
    Piece* capturedPiece = nullptr;
    MoveType moveType = MoveType::Normal;
};