#include "Pawn.h"

bool Pawn::isValidMove(const Move &move, const Board &board) const
{   
    //Guarda a linha e a coluna iniciais
    int startRow = move.start.getRow();
    int startCol = move.start.getCol();

    //Guarda a linha e a coluna de destino
    int destRow = move.destination.getRow();
    int destCol = move.destination.getCol();

    //Verifica se está a tentar mover para a mesma posição 
    if(destRow == startRow && destCol == startCol){
        return false;
    }

    //Se ja houve movimento o peao nao se pode mover 2 casas
    if(hasMoved && (startRow - 1 != destRow)){
        return false;
    }

    

    return true;
}