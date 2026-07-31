#include "Game.h"
#include "Constants.h"

const int width = 1024;
const int height = 1024;

Game::Game() : window(sf::VideoMode(sf::Vector2u(width, height)), "Chess++"){}

void Game::run()
{
    while (window.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents(){

    //Verifica se aconteceu algum evento
    while (const std::optional event = window.pollEvent()){
        
        //Verifica se o evento é fechar a janela do jogo
        //Se sim, fecha a janela
        if (event->is<sf::Event::Closed>()){
            window.close();
        }

        //Verifica se o evento foi click no butao esquerdo do rato
        if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()){
            if(mousePressed->button == sf::Mouse::Button::Left){

                //Fica com a posiçao do rato
                leftClick(mousePressed->position);
                
            }
        }
    }
}

void Game::leftClick(sf::Vector2i mousePosition){
    
    //Divide a posiçao do rato pelo tamanho do quadrado para obter a coluna e linha correta
    int col = mousePosition.x / TILE_SIZE;
    int row = mousePosition.y / TILE_SIZE;

    //Para ter a certeza que o click é dentro to board
    if (row < 0 || row > 7 || col < 0 || col > 7){
        return;
    }
    
    Position clicked(row, col);
    
    if(!selected){
        if(!board.isSquareEmpty(clicked)){
            
            //Guarda a posição
            selectedPosition = clicked;
            selected = true;
        }   
    }
    else{
        
        //Fica com um apontador para a peça que se vai mover
        Piece* selectedPiece = board.getPiece(selectedPosition);
        
        //Cria um movimento
        Move move{ selectedPiece, selectedPosition, clicked };

        //Se existe uma peça no destino, é uma captura
        if(board.getPiece(clicked) != nullptr){
            move.moveType = MoveType::Capture;
        }

        selected = false;

        //Se a move é válidae, entao move a peça
        if(selectedPiece->isValidMove(move, board)){
            board.movePiece(selectedPosition, clicked);
        };
    }
}

void Game::update(){
    //TODO: LOGICA DO JOGO
}

void Game::render()
{
    window.clear();
    renderer.drawBoard(window);
    renderer.drawPieces(window, board);
    window.display();
}