#include <Position.h>

//Construtor
Position::Position(int row, int col) : row(row), col(col) {}

//Retorna a coluna
int Position::getCol() const{
    return col;
}

//Retorna a linha
int Position::getRow() const{
    return row;
}