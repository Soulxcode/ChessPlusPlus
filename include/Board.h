#pragma once
#include <memory>
#include "Piece.h"
#include "Position.h"
#include "enums/DirectionType.h"
#include <vector>

class Board {
    public:
        //Construtor
        Board();
        
        //Metodo que inicializa o board com as posicoes iniciais
        void initialize(); 
        
        //Vai buscar a peça que está na posicao
        Piece* getPiece(const Position &position) const;

        //Move uma peça para outra posiçao, devolve a peca capturada para reverter o movimento se preciso
        std::unique_ptr<Piece> movePiece(const Position &start, const Position &destination);

        //Verifica se a posição está vazia
        bool isSquareEmpty(const Position &position) const;

        //Remove peça da posição 
        bool removePiece(const Position &position);

        //Verifica se o quadrado está a ser atingido por alguem
        bool isSquareAttacked(const Position &position, Color enemyColor) const;

        //Verifica se há peças inimigas em alguma direção
        bool checkDirection(const Position &destination, int rowStep, int colStep, Color enemyColor, DirectionType directionType) const;
        
        //Reverte ultima jogada
        void undoMove(const Position &oldPosition, const Position &newPosition, std::unique_ptr<Piece> capturedPiece);

        //Encontra a posicao do rei
        Position findKing(Color color) const;

        //Verifica se o movimento é legal
        bool isMoveLegal(const Move& move, Color movingColor);

        //Verifica se o jogador está em check
        bool isInCheck(Color color) const;

        //Verifica se ainda existem movimentos que o jogador pode fazer
        bool hasLegalMoves(Color color);

        //Verifica se é checkmate
        bool isCheckmate(Color color);

        //Verifica se é empate tecnico
        bool isStalemate(Color color);

        //Promove peças
        void promotePiece(const Position& position, Color color, PieceType type);

        //Verifica se existe um castle possivel
        bool canCastle(Color color, bool kingside) const;
        
        //Faz o castle
        void castle(Color color, bool kingside);

        //Metodo que verifica se existe a possibilidade de um enpassant
        bool isEnPassantOpportunity(Piece* piece, Position from, Position to) const;

        //Metodo que guarda num vetor os movimentos legais
        std::vector<Position> getValidMoves(Piece* piece, Position position);

        //Atualiza o estado de en passant depois de um movimento 
        void updateEnPassantState(const Position &start, const Position &destination, PieceType movedType);
    
    private:
        //Cria um board 8x8 com uma matriz
        //Cada quadrado tem um apontador para a peca ou nullptr se nenhuma peca
        std::unique_ptr<Piece> squares[8][8];
        
        //Variaveis de en passant
        bool lastMoveWasDoublePawnPush = false;
        Position lastDoublePawnPushDestination{0, 0};
};
