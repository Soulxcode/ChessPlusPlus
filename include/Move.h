#pragma once
#include "enums/MoveType.h"
#include "Position.h"

//Para puder usar o apontador para uma peça
class Piece;

//Estrutura que representa o movimento
struct Move{
    Piece* piece;
    Position start;
    Position destination;
    MoveType moveType = MoveType::Normal;
};