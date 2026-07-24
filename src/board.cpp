#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <memory>


Board::Board()
{
    //Usa o metodo para construir um board novo
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

Piece* Board::getPiece(const Position &position) const
{
    //Retorna o apontador inteligente que está na posicao pedida
    return squares[position.getRow()][position.getCol()].get();
}

bool Board::movePiece(const Position& start, const Position &destination)
{   
    //Se posição inicial estiver vazia retorna falso
    if (getPiece(start) == nullptr)
    { 
        return false; 
    }
    
    //Usa std::move para transferir a propriedade do objeto
    squares[destination.getRow()][destination.getCol()] =
    std::move(squares[start.getRow()][start.getCol()]);

    return true;
}

bool Board::isSquareEmpty(const Position &position) const
{
    //Retorna true se a peça na posição entregue é null
    return getPiece(position) == nullptr;
}

bool Board::removePiece(const Position &position)  
{
    //Se a posiçao tem uma peça, remove e retorna true
    if(getPiece(position) != nullptr){
        squares[position.getRow()][position.getCol()] = nullptr;
        return true;
    };
    return false;
}