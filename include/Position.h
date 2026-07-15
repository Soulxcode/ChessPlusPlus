#pragma once

class Position{
    public:
    Position(int row, int col); //Construtor
    
    int getRow() const; //Vai buscar a linha
    int getCol() const; //Vai buscar a coluna

    private:
        int row; //Linha
        int col; //Coluna
};