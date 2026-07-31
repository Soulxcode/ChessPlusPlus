#pragma once
#include "enums/Color.h"
#include "Move.h"

class Board; 

//Todos os tipos das pecas
enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King };

//Todos os tipos das pecas
class Piece
{
    public:
        //Destructor é usado automaticamente
        virtual ~Piece() = default;

        //Verifica se o movimento é válido
        virtual bool isValidMove(const Move &move, const Board &board) const = 0;

        //Usa o enum para obter o tipo da peça
        virtual PieceType getType() const = 0;

        //Devolve a cor da peça
        Color getColor() const {
            return color;
        };

        //Metodo para assinalar que a peça já se moveu
        void setHasMoved() { hasMoved = true; }
        
        //Metodo para saber se a peça já se moveu
        bool getHasMoved() const { return hasMoved; }
    
    protected:
        //Construtor  
        Piece(Color pieceColor) : color(pieceColor){}
        
        //Controla se a peça já se moveu
        bool hasMoved = false;

    private:
        //Cor da peça
        Color color;
};

