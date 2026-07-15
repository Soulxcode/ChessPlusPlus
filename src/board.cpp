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
        squares[6][i] = WPAWN;
    }

    //Poe em posicao o resto das pecas
    int j = 7;
    for(int i = 0; i < 4; i++){
        if(i == 0){
            squares[0][i] = BROOK;
            squares[0][j] = BROOK;
            squares[7][i] = WROOK;
            squares[7][j] = WROOK;
        } else if (i == 1){
            squares[0][i] = BKNIGHT;
            squares[0][j] = BKNIGHT;
            squares[7][i] = WKNIGHT;
            squares[7][j] = WKNIGHT;
        } else if (i == 2){
            squares[0][i] = BBISHOP;
            squares[0][j] = BBISHOP;
            squares[7][i] = WBISHOP;
            squares[7][j] = WBISHOP;
        }    
        else if(i == 3){
            squares[0][i] = BQUEEN;
            squares[0][j] = BKING;
            squares[7][i] = WQUEEN;
            squares[7][j] = WKING;
        }    
        j--;
   }
}

Piece Board::getPiece(const Position &position) const
{
    //Faz return da peca que está na posicao pedida
    return squares[position.getRow()][position.getCol()];
}

void Board::setPiece(Position &position, Piece piece)
{
    //Coloca uma peca na posicao passada nos parametros
    squares[position.getRow()][position.getCol()] = piece;
}