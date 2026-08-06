#include "Game.h"
#include "Constants.h"

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
    sf::Vector2f viewPos = window.mapPixelToCoords(mousePosition);
    int col = viewPos.x / TILE_SIZE;
    int row = viewPos.y / TILE_SIZE;

    //Para ter a certeza que o click é dentro to board
    if (row < 0 || row > 7 || col < 0 || col > 7){
        return;
    }
    
    Position clicked(row, col);
    
    if(!selected){
        
        Piece* piece = board.getPiece(clicked);

        //Se a cor da peca corresponde ao turno e nao é null fica com a posicao
        if(piece != nullptr && piece->getColor() == currentTurn){
            selectedPosition = clicked;
            selected = true;
        }
    }
    else{

        //Fica com um apontador para a peça que se vai mover
        Piece* selectedPiece = board.getPiece(selectedPosition);

        //Se a peca selecionada ficar nula por alguma razao
        if(selectedPiece == nullptr){
            selected = false;
            return;
        }

        //Cria um movimento
        Move move{ selectedPiece, selectedPosition, clicked };

        //Se existe uma peça no destino, é uma captura
        if(board.getPiece(clicked) != nullptr){
            move.moveType = MoveType::Capture;
        }

        selected = false;

        //Move a peca se o movimento é legal e muda o turno
        if(selectedPiece->isValidMove(move, board)){

            Color enemyColor = (currentTurn == Color::White) ? Color::Black : Color::White;
            
            //Simula o movimento e procura o rei
            std::unique_ptr<Piece> captured = board.movePiece(selectedPosition, clicked);
            Position kingPos = board.findKing(currentTurn);
            
            //Verifica se na nova posicao o rei fica em check
            bool isKingInCheck = board.isSquareAttacked(kingPos, enemyColor);

            //Jogada mata proprio rei por isso reverte movimento
            if(isKingInCheck){
                board.undoMove(selectedPosition, clicked, std::move(captured));

            //Movimento legal se rei nao esta em check
            } else {
                board.movePiece(selectedPosition, clicked);
                selectedPiece->setHasMoved();
                switchTurn();
            }
        };
    }
}

void Game::update(){
    //TODO: LOGICA DO JOGO
}

void Game::render(){
    window.clear();
    renderer.drawBoard(window);
    renderer.drawPieces(window, board);
    window.display();
}

void Game::switchTurn(){
    if(currentTurn == Color::White){
        currentTurn = Color::Black;
    } else{
        currentTurn = Color::White;
    }
}