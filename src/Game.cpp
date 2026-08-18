#include "Game.h"
#include "Constants.h"

Game::Game() : window(sf::VideoMode(sf::Vector2u(width, height)), "Chess++"){}

void Game::run()
{
    while (window.isOpen()){
        processEvents();
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
    
    if(!isSelected){
        
        Piece* piece = board.getPiece(clicked);

        //Se a cor da peca corresponde ao turno e nao é null fica com a posicao
        if(piece != nullptr && piece->getColor() == currentTurn){
            selectedPosition = clicked;
            isSelected = true;
        }
    }
    else{

        //Fica com um apontador para a peça que se vai mover
        Piece* selectedPiece = board.getPiece(selectedPosition);

        //Se a peca selecionada ficar nula por alguma razao
        if(selectedPiece == nullptr){
            isSelected = false;
            return;
        }

        //Cria um movimento
        Move move{ selectedPiece, selectedPosition, clicked };

        //Se existe uma peça no destino, é uma captura
        if(board.getPiece(clicked) != nullptr){
            move.moveType = MoveType::Capture;
        }

        isSelected = false;

        //Move a peça se o movimento é totalmente legal
        if (board.isMoveLegal(move, currentTurn))
        {
            board.movePiece(selectedPosition, clicked);
            selectedPiece->setHasMoved();
            switchTurn();
        }
    }
}

void Game::render(){
    window.clear();
    renderer.drawBoard(window);
    renderer.drawHighlight(window, selectedPosition, isSelected);
    
    //Se existe uma peça selecionada, desenha as ajudas no movimento
    if (isSelected)
    {
        Piece* selectedPiece = board.getPiece(selectedPosition);
        std::vector<Position> validMoves = getValidMoves(selectedPiece, selectedPosition);
        renderer.drawMoveHints(window, validMoves, board);
    }
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

std::vector<Position> Game::getValidMoves(Piece* piece, Position from){
    std::vector<Position> moves;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            //Cria uma posicao teste
            Position test(row, col);

            //Cria um movimento para testar
            Move move{piece, from, test};

            if (board.isMoveLegal(move, piece->getColor()))
            {
                moves.push_back(test);
            }
        }
    }
    return moves;
}