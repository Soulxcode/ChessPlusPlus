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

    //Se peao for branco
    if(getColor() == Color::White){
        
        //Se ja houve movimento o peao nao se pode mover 2 casas
        if(hasMoved && (startRow - 1 != destRow) && startCol == destCol){
        return false;

        //Se ainda nao houve movimento pode se mover 2 casas
        //Verifica se há pecas no caminho
        } else if(!hasMoved && (startRow - 2 == destRow) && startCol == destCol){
            if(board.isSquareEmpty(move.destination)){
            
                //Cria a posição do meio (uma casa à frente do início)
                Position middlePos(startRow - 1, startCol);
                if(board.isSquareEmpty(middlePos)){
                    return true;
                } else {
                    return false;
                }

            } else {
                return false;
            }
        }

        //Verifica se existe alguma peça no caminho 
        if(startRow - 1 == destRow && startCol == destCol 
            && board.getPiece(move.destination) == nullptr){
                return true;
            }

        //Verifica se a peça que está na diagonal existe e é inimiga
        if(destCol == startCol + 1 || destCol == startCol - 1){
            if(board.getPiece(move.destination) != nullptr 
            && board.getPiece(move.destination)->getColor() == Color::Black
            && destRow + 1 == startRow){
                
                return true;
            } else {
                return false;
            }
        }

    }
    
    //Se peao for preto
    if(getColor() == Color::Black){
    
        //Se ja houve movimento o peao nao se pode mover 2 casas
        if(hasMoved && (startRow + 1 != destRow) && startCol == destCol){
            return false;

        //Se ainda nao houve movimento pode se mover 2 casas
        //Verifica se há peças no caminho
        } else if(!hasMoved && (startRow + 2 == destRow) && startCol == destCol){
            if(board.isSquareEmpty(move.destination)){
                
                //Cria a posição do meio (uma casa à frente do início)
                Position middlePos(startRow + 1, startCol);
                if(board.isSquareEmpty(middlePos)){
                    return true;
                }
            }
            return false;
        }

        //Verifica se existe alguma peça no caminho 
        if(startRow + 1 == destRow && startCol == destCol 
            && board.getPiece(move.destination) == nullptr){
                return true;
            }

        //Verifica se a peça que está na diagonal existe e é inimiga
        if(destCol == startCol + 1 || destCol == startCol - 1){
            if(board.getPiece(move.destination) != nullptr 
            && board.getPiece(move.destination)->getColor() == Color::White
            && destRow - 1 == startRow){
                
                return true;
            } else {
                return false;
            }
        }
    }

    return false;
}