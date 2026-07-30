#pragma once
#include <memory>
#include "Piece.h"
#include "Position.h"

class Board {
    public:
        //Construtor
        Board();
        
        //Metodo que inicializa o board com as posicoes iniciais
        void initialize(); 
        
        //Vai buscar a peça que está na posicao
        Piece* getPiece(const Position &position) const;

        //Move uma peça para outra posiçao
        void movePiece(const Position &start, const Position& destination);

        //Verifica se a posição está vazia
        bool isSquareEmpty(const Position &position) const;

        //Remove peça da posição 
        bool removePiece(const Position &position);
    
    private:
        //Cria um board 8x8 com uma matriz
        //Cada quadrado tem um apontador para a peça a o ocupar ou nullptr se nao tiver nenhuma peça
        std::unique_ptr<Piece> squares[8][8]; 
};
