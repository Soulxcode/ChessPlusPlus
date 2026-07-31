#include "Pawn.h"
#include "Board.h"

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

    if(getColor() == Color::White){
        
        //Se ja houve movimento o peao nao se pode mover 2 casas
        if(hasMoved && (startRow - 1 != destRow) && startCol == destCol){
        return false;

        //Se ainda nao houve movimento pode se mover 2 casas
        } else if(!hasMoved && (startRow - 2 == destRow) && startCol == destCol){
            if(board.getPiece(move.destination) == nullptr){
                return true;
            } else {
                return false;
            }
        }

        //Verifica se existe alguma peça no caminho 
        if(startRow - 1 == destRow && startCol == destCol 
            && board.getPiece(move.destination) != nullptr){
                return false;
            }

        //Verifica se a peça que está na diagonal existe e é inimiga
        if(startCol != destCol){
            if(board.getPiece(move.destination) != nullptr 
            && board.getPiece(move.destination)->getColor() == Color::Black
            && destRow + 1 == startRow){
                
                return true;
            } else {
                return false;
            }
        }

    }
    if(getColor() == Color::Black){
        if(hasMoved && (startRow + 1 != destRow)){
        return false;
        }
    }

    return true;
}