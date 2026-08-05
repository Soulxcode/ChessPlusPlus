#include "Knight.h"
#include "Board.h"

bool Knight::isValidMove(const Move &move, const Board &board) const
{
    //Guarda a linha e a coluna iniciais
    int startRow = move.start.getRow();
    int startCol = move.start.getCol();

    //Guarda a linha e a coluna de destino
    int destRow = move.destination.getRow();
    int destCol = move.destination.getCol();

    //Lista de movimentos validas de cavaleiros
    int knightsPositions[8][2] = { 
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    //Faz um loop nas posicoes para encontrar uma posicao legal
    for (auto& kPosition : knightsPositions){
        
        //A diferenca para procurar um movimento legal
        int diffRow = startRow - destRow;   
        int diffCol = startCol - destCol;
        
        //Procura um movimento válido 
        if(diffRow == kPosition[0] && diffCol == kPosition[1]){
            
            Piece* destPiece = board.getPiece(move.destination);

            //Verifica se existe uma peca da mesma equipa no quadrado
            if (destPiece != nullptr && destPiece->getColor() == getColor()) {
                return false;
            }   

            return true;      
        }
    }
    return false;
}