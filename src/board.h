#pragma once
#include "Piece.h"

class Board {
    public:
        Board(); //Construtor

        //Metodos para mudarem o estado do board
        void initialize(); //Metodo que inicializa o board com as posicoes iniciais
        
        Piece getPiece(int row, int col) const; //Vai buscar a peça que está naquela coluna e linha
        
        void setPiece(int row, int col, Piece piece); //Muda posicao da peça  
    
    private:
        //Cria um board 8x8 com uma matriz
        //Cada membro é um apontador para uma peça
        Piece squares[8][8]; 

};
