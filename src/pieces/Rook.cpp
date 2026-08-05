#include "Rook.h"
#include "Board.h"
#include "Constants.h"

bool Rook::isValidMove(const Move &move, const Board &board) const
{   
    //Guarda a linha e a coluna iniciais
    int startRow = move.start.getRow();
    int startCol = move.start.getCol();

    //Guarda a linha e a coluna de destino
    int destRow = move.destination.getRow();
    int destCol = move.destination.getCol();

    //Nao se pode mover na linha e na coluna ao mesmo tempo
    if(startRow != destRow && startCol != destCol){
        return false;
    }
    
    //Movimento ilegal, destino igual ao começo
    if(destRow == startRow && destCol == startCol){
        return false;
    }

    //Para onde vai andar na linha
    int rowStep = 0;

    //Se a posição do destino é maior que o começo entao anda para baixo
    if(destRow > startRow){
        rowStep = DOWN;
    }
    //Se o começo for maior anda para cima
    else if(destRow < startRow){
        rowStep = UP;
    }

    //Para onde vai andar na coluna
    int colStep = 0;

    //Destino maior, anda para a direita
    if(destCol > startCol){
        colStep = RIGHT;
    }
    //Destino menor, anda para a esquerda
    else if(destCol < startCol){
        colStep = LEFT;
    }

    //Soma pela a primeira vez para começar a verificar se esta no destino
    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    //Enquanto não estiver no destino
    while (currentRow != destRow || currentCol != destCol){
        
        //Cria uma posição da coluna e linha que estamos neste momento
        Position currentPos(currentRow, currentCol);

        //Se a posição está ocupada movimento ilegal
        if (!board.isSquareEmpty(currentPos)){
            return false;
        }
        
        //Continua a adicionar até chegar ao destino
        currentRow += rowStep;
        currentCol += colStep;
    }

    //Cria um apontador para a peça no destino
    Piece* destPiece = board.getPiece(move.destination);

    //Se a peça nao é null mas a cor é a mesma que a torre a ser usada
    if (destPiece != nullptr && destPiece->getColor() == getColor()){
        return false; 
    }
    
    //Se chegar aqui ou é uma peça inimiga ou um lugar vazio, movimento legal
    return true; 
}