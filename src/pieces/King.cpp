#include "King.h"
#include "Board.h"

bool King::isValidMove(const Move &move, const Board &board) const
{
    //Guarda a linha e a coluna iniciais
    int startRow = move.start.getRow();
    int startCol = move.start.getCol();

    //Guarda a linha e a coluna de destino
    int destRow = move.destination.getRow();
    int destCol = move.destination.getCol();

    //Movimento ilegal, destino igual ao começo
    if(destRow == startRow && destCol == startCol){
        return false;
    }

    //A linha deve ser igual, +1 ou -1
    if (destRow != startRow && destRow != startRow + 1 
        && destRow != startRow - 1) {
        return false;
    }

    //A coluna deve ser igual, +1 ou -1
    if (destCol != startCol && destCol != startCol + 1 
        && destCol != startCol - 1) {
        return false;
    }

    //Não pode capturar uma peça da mesma cor
    Piece* destinationPiece = board.getPiece(move.destination);
    if(destinationPiece != nullptr && destinationPiece->getColor() == getColor()){
        return false;
    }

    //Determina a cor inimiga
    Color enemyColor = (getColor() == Color::White) ? Color::Black : Color::White;

    //Guarda o tipo da peça
    PieceType pieceType = getType();

    //O rei não pode mover-se para uma casa atacada
    if(board.isSquareAttacked(move.destination, enemyColor)){
        return false;
    }
    
    return true;
}