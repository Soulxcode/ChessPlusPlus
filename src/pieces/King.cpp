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

    //Checks para verificar que o rei nao se mete em check
    //Rei branco
    if(getColor() == Color::White){

        //Movimento ilegal se a peça for da mesma cor 
        if(board.getPiece(move.destination) != nullptr 
        && board.getPiece(move.destination)->getColor() == Color::White ){
            return false;
        }

        //Guarda as posicoes das diagonais
        Position left(destRow - 1, destCol - 1);
        Position right(destRow - 1, destCol + 1);

        //Guarda o apontador para as peças
        Piece* leftPiece = board.getPiece(left);
        Piece* rightPiece = board.getPiece(right);

        //Se exister um rei ou peao inimigo, movimento ilegal
        if(leftPiece != nullptr && 
            leftPiece->getColor() == Color::Black &&
            (leftPiece->getType() == PieceType::King ||
            leftPiece->getType() == PieceType::Pawn )){
            
            return false;
        }

        if(rightPiece != nullptr &&
            rightPiece->getColor() == Color::Black &&
            (rightPiece->getType() == PieceType::Pawn ||
            rightPiece->getType() == PieceType::King)){
            
            return false;
        }

    }
    
    return true;
}