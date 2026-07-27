#pragma once
#include "MoveType.h"
#include "Position.h"

class Piece; // forward declaration

//Estrutura que representa o movimento
struct Move{
    Piece* piece;
    Position start;
    Position destination;
    MoveType moveType = MoveType::Normal;
};