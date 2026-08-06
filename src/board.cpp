#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Constants.h"
#include <iostream>
#include <memory>


Board::Board(){
    
    initialize(); 
}
    
void Board::initialize()
{
    //Cada quadrado guarda um apontador inteligente para os peoes
    for(int i = 0; i < 8; i++){
        squares[1][i] = std::make_unique<Pawn>(Color::Black);
        squares[6][i] = std::make_unique<Pawn>(Color::White);
    }

    //Cada quadrado guarda um apontador inteligente para o resto das peças
    int j = 7;
    for(int i = 0; i < 4; i++){
        if(i == 0){
            squares[0][i] = std::make_unique<Rook>(Color::Black);
            squares[0][j] = std::make_unique<Rook>(Color::Black);
            squares[7][i] = std::make_unique<Rook>(Color::White);
            squares[7][j] = std::make_unique<Rook>(Color::White);
        } else if (i == 1){
            squares[0][i] = std::make_unique<Knight>(Color::Black);
            squares[0][j] = std::make_unique<Knight>(Color::Black);
            squares[7][i] = std::make_unique<Knight>(Color::White);
            squares[7][j] = std::make_unique<Knight>(Color::White);
        } else if (i == 2){
            squares[0][i] = std::make_unique<Bishop>(Color::Black);
            squares[0][j] = std::make_unique<Bishop>(Color::Black);
            squares[7][i] = std::make_unique<Bishop>(Color::White);
            squares[7][j] = std::make_unique<Bishop>(Color::White);
        } else if(i == 3){
            squares[0][i] = std::make_unique<Queen>(Color::Black);
            squares[0][j] = std::make_unique<King>(Color::Black);
            squares[7][i] = std::make_unique<Queen>(Color::White);
            squares[7][j] = std::make_unique<King>(Color::White);
        }    
        j--;
   }
}

Piece* Board::getPiece(const Position &position) const{
    
    //Se a posiçao está fora do board entao é null
    if (position.getRow() < 0 || position.getRow() >= 8 || position.getCol() < 0 || position.getCol() >= 8){
        return nullptr;
    }

    //Retorna o apontador inteligente que está na posicao pedida
    return squares[position.getRow()][position.getCol()].get();
}

std::unique_ptr<Piece> Board::movePiece(const Position& start, const Position &destination){   

    //Nada para mover
    if(getPiece(start) == nullptr){
        return nullptr;
    }

    //Guarda a peca que vai ser capturada
    std::unique_ptr<Piece> captured = std::move(squares[destination.getRow()][destination.getCol()]);

    //Usa std::move para transferir a propriedade do objeto
    squares[destination.getRow()][destination.getCol()] = 
    std::move(squares[start.getRow()][start.getCol()]);
    
    return captured;
}

bool Board::isSquareEmpty(const Position &position) const{

    //Retorna true se a peça na posição entregue é null
    return getPiece(position) == nullptr;
}

bool Board::removePiece(const Position &position){

    //Se a posiçao tem uma peça, remove
    if(getPiece(position) != nullptr){
        squares[position.getRow()][position.getCol()] = nullptr;
        return true;
    }
    return false;
}

bool Board::checkDirection(const Position &destination, int rowStep, int colStep, Color enemyColor, DirectionType directionType) const {

    //Recebe as posiçoes a beira da posiçao destino
    int row = destination.getRow() + rowStep;
    int col = destination.getCol() + colStep;

    //Enquanto que a posição for dentro do board
    while(row >= 0 && row < 8 && col >= 0 && col < 8){

        //Ve se existe alguma peça naquela 
        Piece* piece = getPiece(Position(row, col));

        //Se nao existe passa á proxima posição
        if(piece == nullptr){
            row += rowStep;
            col += colStep;
            continue;
        }

        //Ignora a si mesmo quando verifica a posiçao
        if(piece->getType() == PieceType::King && piece->getColor() != enemyColor){
            row += rowStep;
            col += colStep;
            continue;
        }   

        //Se a peça é inimiga verificar se existe perigo
        if(piece->getColor() == enemyColor){
            if(directionType  == DirectionType::Diagonal){
                if(piece->getType() == PieceType::Bishop || piece->getType() == PieceType::Queen){
                    return true;
                }
            }
            if(directionType == DirectionType::Straight){
                if(piece->getType() == PieceType::Rook || piece->getType() == PieceType::Queen){
                    return true;
                }
            }
        }
        //Encontrou peça que nao apresenta perigo
        return false;
    }
    //Nao existia peças
    return false;
}

bool Board::isSquareAttacked(const Position &position, Color enemyColor) const{
    
    //Verifica as diagonais por rainhas e bispos
    if(checkDirection(position, UP, LEFT, enemyColor, DirectionType::Diagonal))
        return true;

    if(checkDirection(position, UP, RIGHT, enemyColor, DirectionType::Diagonal))
        return true;

    if(checkDirection(position, DOWN, LEFT, enemyColor, DirectionType::Diagonal))
        return true;

    if(checkDirection(position, DOWN, RIGHT, enemyColor, DirectionType::Diagonal))
        return true;

    //Verifica vertical e horizontal por rainhas e torres
    if(checkDirection(position, UP, 0, enemyColor, DirectionType::Straight))
        return true;

    if(checkDirection(position, DOWN, 0, enemyColor, DirectionType::Straight))
        return true;    

    if(checkDirection(position, 0, LEFT, enemyColor, DirectionType::Straight))
        return true;

    if(checkDirection(position, 0, RIGHT, enemyColor, DirectionType::Straight))
        return true;    
    
    //Verifica se ha peoes a atacar
    int pawnRow = (enemyColor == Color::White) ? position.getRow() + DOWN : position.getRow() + UP;

    //Vai buscar as posiçoes dos peoes
    Position leftPawn(pawnRow, position.getCol() + LEFT);
    Position rightPawn(pawnRow, position.getCol() + RIGHT);

    //Verifica se existe peao na diagonal LEFT
    Piece* piece = getPiece(leftPawn);
    if(piece != nullptr && piece->getColor() == enemyColor && piece->getType() == PieceType::Pawn){
        return true;
    }

    //Verifica se existe peao na diagonal RIGHT
    piece = getPiece(rightPawn);
    if(piece != nullptr && piece->getColor() == enemyColor && piece->getType() == PieceType::Pawn){
        return true;
    }
    
    //Cavaleiros
    //Lista de posicoes validas de cavaleiros
    int knightsPositions[8][2] = { 
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    //Faz loop por todas as possiveis posiçoes do cavaleiro
    for (auto& kPosition : knightsPositions){
        int row = position.getRow() + kPosition[0];
        int col = position.getCol() + kPosition[1];
        
        //Verifica se está dentro do board
        if(row >= 0 && row < 8 && col >= 0 && col < 8){
            Position knightPosition(row, col);
            Piece* piece = getPiece(knightPosition);

            //Verifica se existe um cavaleiro inimigo na posicao guardada
            if(piece != nullptr && piece->getType() == PieceType::Knight && piece->getColor() == enemyColor ){
                return true;
            }
        } 
    }

    //Verificar se ha um rei adjacente
    for(int row = -1; row < 2; row++){
        for(int col = -1; col < 2 ; col++){
            if(row == 0 && col == 0){
                continue;
            }

            int testRow = position.getRow() + row;
            int testCol = position.getCol() + col;

            //Verifica se está dentro do board
            if(testRow >= 0 && testRow < 8 && testCol >= 0 && testCol < 8){

                Position adjacent(testRow, testCol);
                Piece* piece = getPiece(adjacent);

                if(piece != nullptr && piece->getType() == PieceType::King && piece->getColor() == enemyColor){
                    return true;
                }
            }
        }
    }

    return false;

}

Position Board::findKing(Color color) const{
    
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            
            //Fica com a posicao e com a peca correspondentes 
            Position position(row, col);
            Piece* piece = getPiece(position);
            
            //Verifica se a peca e o rei procurado
            if(piece != nullptr){
                if(piece->getType() == PieceType::King && piece->getColor() == color){
                    return position;
                }
            }
             
        }
    }
    
    //Se por alguma razao nao encontrar o rei no tabuleiro(wtf?)
    //Retorna uma posicao fora do tabuleiro
    return Position(-1, -1);
}

void Board::undoMove(const Position &oldPosition, const Position &newPosition, std::unique_ptr<Piece> capturedPiece){
    
    //Move a peca para a antiga posicao
    squares[oldPosition.getRow()][oldPosition.getCol()] = std::move(squares[newPosition.getRow()][newPosition.getCol()]);

    //Restaura a peca capturada ou nullptr 
    squares[newPosition.getRow()][newPosition.getCol()] = std::move(capturedPiece);
}