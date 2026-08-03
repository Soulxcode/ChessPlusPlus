#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
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

void Board::movePiece(const Position& start, const Position &destination){   

    //Usa std::move para transferir a propriedade do objeto
    squares[destination.getRow()][destination.getCol()] = 
    std::move(squares[start.getRow()][start.getCol()]);
}

bool Board::isSquareEmpty(const Position &position) const{

    //Retorna true se a peça na posição entregue é null
    return getPiece(position) == nullptr;
}

bool Board::removePiece(const Position &position){

    //Se a posiçao tem uma peça, remove e retorna true
    if(getPiece(position) != nullptr){
        squares[position.getRow()][position.getCol()] = nullptr;
        return true;
    };
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
    if(checkDirection(position, -1, -1, enemyColor, DirectionType::Diagonal))
        return true;

    if(checkDirection(position, -1, 1, enemyColor, DirectionType::Diagonal))
        return true;

    if(checkDirection(position, 1, -1, enemyColor, DirectionType::Diagonal))
        return true;

    if(checkDirection(position, 1, 1, enemyColor, DirectionType::Diagonal))
        return true;

    //Verifica vertical e horizontal por rainhas e torres
    if(checkDirection(position, -1, 0, enemyColor, DirectionType::Straight))
        return true;

    if(checkDirection(position, 1, 0, enemyColor, DirectionType::Straight))
        return true;    

    if(checkDirection(position, 0, -1, enemyColor, DirectionType::Straight))
        return true;

    if(checkDirection(position, 0, 1, enemyColor, DirectionType::Straight))
        return true;    
    
    //Verifica se ha peoes a atacar
    int pawnRow = (enemyColor == Color::White) ? position.getRow() + 1 : position.getRow() - 1;

    //Vai buscar as posiçoes dos peoes
    Position leftPawn(pawnRow, position.getCol() - 1);
    Position rightPawn(pawnRow, position.getCol() + 1);

    //Verifica se existe peao na diagonal esquerda
    Piece* piece = getPiece(leftPawn);
    if(piece != nullptr && piece->getColor() == enemyColor && piece->getType() == PieceType::Pawn){
        return true;
    }

    //Verifica se existe peao na diagonal direita
    piece = getPiece(rightPawn);
    if(piece != nullptr && piece->getColor() == enemyColor && piece->getType() == PieceType::Pawn){
        return true;
    }
    
    return false;

}