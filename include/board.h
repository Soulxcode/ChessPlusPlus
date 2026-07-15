#pragma once
#include "Piece.h"
#include "Position.h"

class Board {
    public:
        Board(); //Construtor

        //Metodos para mudarem o estado do board
        void initialize(); //Metodo que inicializa o board com as posicoes iniciais
        
        Piece getPiece(Position position) const; //Vai buscar a peça que está na posicao
        void setPiece(Position position, Piece piece); //Muda posicao da peça  
    
    private:
        //Cria um board 8x8 com uma matriz
        //Cada membro é um apontador para uma peça
        Piece squares[8][8]; 

};
