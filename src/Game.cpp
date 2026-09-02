#include "Game.h"
#include "Constants.h"

Game::Game() : window(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT)), "Chess++"){}

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

                //Se o jogo acabou
                if (gameOver){
                    if (renderer.isRematchButtonClicked(mousePressed->position)){
                        resetGame();
                    }
                }

                //Verifica se está á espera de uma promoçao, se nao, fica com o click do rato
                waitingPromotion ? promotionClick(mousePressed->position) : leftClick(mousePressed->position);
            }
        }
    }
}

void Game::leftClick(sf::Vector2i mousePosition){

    //Para nao ser possivel selecionar peças depois do jogo acabar
    if (gameOver){
        return;
    }
    
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
    
    } else{

        //Fica com um apontador para a peça que se vai mover
        Piece* selectedPiece = board.getPiece(selectedPosition);

        //Se a peca selecionada ficar nula por alguma razao
        if(selectedPiece == nullptr){
            isSelected = false;
            return;
        }

        //Verifica se é da mesma equipa sem ser a mesma peça
        Piece* clickedPiece = board.getPiece(clicked);
        if (clickedPiece != nullptr && clickedPiece->getColor() == currentTurn 
            && !(clicked.getRow() == selectedPosition.getRow() && clicked.getCol() == selectedPosition.getCol())){
            selectedPosition = clicked;
            return;
            }
        
        //Se a peça é um rei, verifica se é um castle
        if(selectedPiece->getType() == PieceType::King){

            //Verifica se a coluna escolhida para o movimento é valida para um castle
            int colDiff = clicked.getCol() - selectedPosition.getCol();

            if(colDiff == 2 || colDiff == -2){
                bool kingside = (colDiff == 2);

                if(board.canCastle(currentTurn, kingside)){
                    board.castle(currentTurn, kingside);
                    switchTurn();
                }

                isSelected = false;
                return;
            }
        }

        //Cria um movimento
        Move move{ selectedPiece, selectedPosition, clicked };

        //Se existe uma peça no destino, é uma captura
        if(clickedPiece != nullptr){
            move.moveType = MoveType::Capture;
        }

        //Verifica se é enpassant
        else if(board.isEnPassantOpportunity(selectedPiece, selectedPosition, clicked)){
            move.moveType = MoveType::EnPassant;
        }

        isSelected = false;

        //Move a peça se o movimento é totalmente legal
        if (board.isMoveLegal(move, currentTurn)){
            
            PieceType movedType = selectedPiece->getType();
            board.movePiece(selectedPosition, clicked);
            selectedPiece->setHasMoved();

            //Atualiza se o en passnt é possivel
            board.updateEnPassantState(selectedPosition, clicked, movedType);

            //Se foi uma captura en passant, remove o peão capturado (que está ao lado, não no destino)
            if (move.moveType == MoveType::EnPassant){
                Position capturedPawnPos(selectedPosition.getRow(), clicked.getCol());
                board.removePiece(capturedPawnPos);
            }
            
            //Se a peça selecionada é um peao verifica se é uma promoção
            if (selectedPiece->getType() == PieceType::Pawn){
                
                //Verifica se esta na ultima linha da cor do jogador atual
                int finalRow = (currentTurn == Color::White) ? 0 : 7;

                //Se esta na ultima linha fica a espera a escolha do jogador
                if (clicked.getRow() == finalRow){
                    waitingPromotion = true;
                    promotionPosition = clicked;
                    promotionColor = currentTurn;
                    return;
                }
            }
            
            switchTurn();
        }
    }
}

void Game::render(){
    
    window.clear();
    renderer.drawBoard(window);
    renderer.drawHighlight(window, selectedPosition, isSelected);
    
    //Se existe uma peça selecionada, desenha as ajudas no movimento
    if (isSelected){
        Piece* selectedPiece = board.getPiece(selectedPosition);
        std::vector<Position> validMoves = board.getValidMoves(selectedPiece, selectedPosition);
        renderer.drawMoveHints(window, validMoves, board);
    }
    
    renderer.drawPieces(window, board);

    //Se existe uma promocao, desenha as opcoes de promocao
    if (waitingPromotion){
        renderer.drawPromotionOptions(window, promotionPosition, promotionColor);
    }

    //Se é checkmate mostra a mensagem de quem ganhou
    if (board.isCheckmate(currentTurn)){
        
        //Verifica quem ganhou para mostrar o texto
        std::string winnerText = currentTurn == Color::White ? winnerText = "BLACK WINS" : winnerText = "WHITE WINS";
        renderer.drawGameOver(window, winnerText);
        renderer.drawRematchButton(window);
        gameOver = true;    
    }
    
    //Se é empate   
    else if (board.isStalemate(currentTurn)){
        renderer.drawGameOver(window, "DRAW");
        renderer.drawRematchButton(window);
        gameOver = true;
    }
    window.display();
}

void Game::switchTurn(){
    currentTurn = (currentTurn == Color::White) ? Color::Black : Color::White;
}

void Game::promotionClick(sf::Vector2i mousePosition){

    //Divide a posiçao do rato pelo tamanho do quadrado para obter a coluna e linha correta
    sf::Vector2f viewPos = window.mapPixelToCoords(mousePosition);
    int col = viewPos.x / TILE_SIZE;
    int row = viewPos.y / TILE_SIZE;

    //Click fora da coluna das opções, ignora
    if (col != promotionPosition.getCol()){
        return; 
    }

    //Se a promocao é na posicao 0, as opcçoes sao desenhadas para baixo, se nao para cima
    int direction = (promotionPosition.getRow() == 0) ? DOWN : UP;

    //Calcula a opcao que o jogador escolheu
    int optionIndex = (row - promotionPosition.getRow()) * direction;

    //Click fora das opções, ignora
    if (optionIndex < 0 || optionIndex > 3){
        return; 
    }
    
    PieceType chosenType;
    switch (optionIndex)
    {
        case 0: chosenType = PieceType::Queen; break;
        case 1: chosenType = PieceType::Rook; break;
        case 2: chosenType = PieceType::Bishop; break;
        case 3: chosenType = PieceType::Knight; break;
    }

    //Promove a peça de acordo com a escolha do jogador
    board.promotePiece(promotionPosition, promotionColor, chosenType);

    waitingPromotion = false;
    switchTurn();
}

void Game::resetGame()
{
    //Recria o board do zero
    board = Board();

    //Reinicia todo o estado do jogo
    currentTurn = Color::White;
    isSelected = false;
    gameOver = false;
    waitingPromotion = false;
}