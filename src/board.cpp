#include "Board.h"
#include <iostream>


Board::Board()
{
    //Usa o metodo para construir um board novo
    initialize(); 
}
    
void Board::initialize()
{
    //2 loops para percorrer a matriz e dar o valor de empty a todas as posicoes    
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
                squares[row][col] = EMPTY;
        }
    }

    //Poe em posicao os peoes todos
    for(int i = 0; i < 8; i++){
        squares[1][i] = BPAWN;
        squares[7][i] = WPAWN;
    }
}

Piece Board::getPiece(int row, int col) const
{
    //Faz return da peca que está na posicao pedida
    return squares[row][col];
}

void Board::setPiece(int row, int col, Piece piece)
{
    //Coloca uma peca na posicao passada nos parametros
    squares[row][col] = piece;
}