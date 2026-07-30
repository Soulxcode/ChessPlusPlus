#include "Rook.h"

bool Rook::isValidMove(const Move &move, const Board &board) const
{
    int startRow = move.start.getRow();
    int startCol = move.start.getCol();

    int destRow = move.destination.getRow();
    int destCol = move.destination.getCol();

    if(destRow != startRow || destCol != startCol){
        return false;
    }
    

}