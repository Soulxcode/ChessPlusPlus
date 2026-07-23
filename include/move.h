#pragma once
#include "Piece.h"
#include "MoveType.h"

//Estrutura que representa o movimento
struct Move{
    Piece* piece;
    Position start;
    Position destination;
    MoveType moveType = MoveType::Normal;
};