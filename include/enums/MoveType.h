#pragma once

//Tipo de movimentos possiveis
enum class MoveType{
    Normal,
    Capture,
    Castle,
    EnPassant,
    Promotion
};