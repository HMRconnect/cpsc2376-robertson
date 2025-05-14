#include "game.h"

int intInputValid()
{
	int num{};
	while (true)
	{
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cout << "Invalid. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	return num;
}

int moveValidator()
{
	int num{};
	while (true)
	{
		num = intInputValid();
		if (num > 7 or num < 0)
		{
			std::cout << "Invalid. ";
			continue;
		}
		break;
	}
	return num;
}


	Game::Game() {};

	//initializes board
	//had trouble initializing it correctly in constructor so copied from prev ver
	void Game::makeBoard()
	{
		std::array <std::array<Player, 8>, 8 > emptyBoard
		{ {
			{Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::white,Player::black, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::black,Player::white, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,},
			{Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,Player::empty, Player::empty,},

		} };
		board = emptyBoard;
	}

	

	Player Game::getOpponent(Player player)
	{
		if (player == Player::white)
		{
			return Player::black;
		}
		else
		{
			return Player::white;
		}
	}


	//check if its inside the board still
	bool Game::isInsideBoard(int row, int column)
	{
		return row >= 0 && row < 8 && column >= 0 && column < 8;
	}



	//find pieces that can be converted in a direction depending on offset, return list
	//should only be passed empty spaces
	std::vector<Position> Game::convertedPieces(Position position, Player player, int rowOffset, int columnOffset)
	{
		std::vector<Position> convertedList{};
		Position currentPosition{};
		currentPosition.row = position.row + rowOffset;
		currentPosition.column = position.column + columnOffset;
		while (isInsideBoard(currentPosition.row, currentPosition.column) && board.at(currentPosition.row).at(currentPosition.column) != Player::empty)
		{
			if (board.at(currentPosition.row).at(currentPosition.column) == getOpponent(player))
			{
				Position enemyPosition{ currentPosition.row, currentPosition.column };
				convertedList.push_back(enemyPosition);
				currentPosition.row += rowOffset;
				currentPosition.column += columnOffset;
			}
			else if (board.at(currentPosition.row).at(currentPosition.column) == player)
			{
				return convertedList;
			}
		}
		return std::vector<Position>{};
	}

	//returns list of valid convertable spots for all directions
	std::vector<Position> Game::checkDirections(Position position, Player player)
	{
		std::vector<Position> convertedList{};
		for (int rowOffset = -1; rowOffset <= 1; rowOffset++)
		{
			for (int columnOffset = -1; columnOffset <= 1; columnOffset++)
			{
				if (rowOffset == 0 && columnOffset == 0)
				{
					continue;
				}
				std::vector<Position> directionList = convertedPieces(position, player, rowOffset, columnOffset);
				convertedList.insert(convertedList.end(), directionList.begin(), directionList.end());
			}
		}
		return convertedList;
	}

	//returns true if the move is legal, false if it is not
	bool Game::canPieceMove(Position movePosition, Player player)
	{
		std::vector<Position> legalMovesList = checkDirections(movePosition, player);
		if (board.at(movePosition.row).at(movePosition.column) != Player::empty)
		{
			return false;
		}
		if (legalMovesList.size() == 0)
		{
			return false;
		}
		return true;
	}

	void Game::setLegalMoves(Player player)
	{
		std::vector<MoveInfo> legalMoves{};
		for (int i{ 0 }; i < board.size(); i++)
		{
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				Position currentPosition{ i,j };
				if (canPieceMove(currentPosition, player))
				{
					MoveInfo validMove{};
					validMove.moverPlayer = player;
					validMove.position = currentPosition;
					validMove.convertablePieces = checkDirections(currentPosition, player);
					legalMoves.push_back(validMove);
				}
			}
		}
		if (player == Player::white)
		{
			whiteLegalMoveList = legalMoves;
		}
		else
		{
			blackLegalMoveList = legalMoves;
		}
	}

	void Game::setColorCounts()
	{
		for (int i{ 0 }; i < board.size(); i++)
		{
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				if (board.at(i).at(j) == Player::white)
				{
					whiteCount++;
				}
				else if (board.at(i).at(j) == Player::black)
				{
					blackCount++;
				}
			}
		}
	}

	void Game::convertPieces(std::vector<Position> convertPositions)
	{
		for (int i{ 0 }; i < convertPositions.size(); i++)
		{
			board.at(convertPositions.at(i).row).at(convertPositions.at(i).column) = currentPlayer;
		}
	}

	void Game::makeMove(Position position)
	{
		std::vector<Position> convertPositions = checkDirections(position, currentPlayer);
		convertPieces(convertPositions);
		setColorCounts();
	}



	void Game::play(Position pos)
	{
		if (canPieceMove(pos, currentPlayer) == true)
		{
			//set selected spot to correct piece
			board.at(pos.row).at(pos.column) = currentPlayer;
			//convert pieces between to correct color
			makeMove(pos);
			//then end the while loop & return to main to reprint the board & call next turn
			return;
		}
		else
		{
			std::cout << "That is not a legal move, please try again." << std::endl;
			return;
		}
		
	}

	void Game::checkBoardFullness()
	{
		for (int i{ 0 }; i < board.size(); i++)
		{
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				if (board.at(i).at(j) == Player::empty)
				{
					gameStatus = ongoing; // The board is not full, the game continues
					return;
				}
			}
		}
		gameStatus = finished; //each spot has been checked and no space is empty, game is over
	}

	GameStatus Game::getStatus()
	{
		return gameStatus;
	}

	Player Game::getCurrentPlayer()
	{
		return currentPlayer;
	}
	
	void Game::setCurrentPlayer(Player player)
	{
		currentPlayer = player;
	}

	void Game::setTurn(Player nextPlayer)
	{
		currentPlayer = nextPlayer;
	}




	void Game::renderBoard(SDL_Renderer*& renderer)
	{

		//board background
		SDL_SetRenderDrawColor(renderer, 51, 37, 16, 255);
		SDL_RenderFillRect(renderer, &boardBorder);
		SDL_SetRenderDrawColor(renderer, 12, 153, 31, 255);
		SDL_RenderFillRect(renderer, &boardBack);

		
		int x{ 165 };
		int y{ 65 };
		for (int i{ 0 }; i < board.size(); i++)
		{
			
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				SDL_Rect boardTile{ x, y, 50, 50 };
				SDL_SetRenderDrawColor(renderer, 50,50,50,50);
				SDL_RenderFillRect(renderer, &boardTile);
				x += 60;
			}
			x = 165;
			y += 60;
		}
	}

	void Game::renderPieces(SDL_Renderer*& renderer)
	{
		int x{ 190 };
		int y{ 90 };
		for (int i{ 0 }; i < board.size(); i++)
		{
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				if (board.at(i).at(j) == Player::empty)
				{
					filledCircleRGBA(renderer, x, y, 20, 0, 0, 0, 0);
				}
				else if (board.at(i).at(j) == Player::white)
				{
					filledCircleRGBA(renderer, x, y, 20, 255, 255, 255, 255);
				}
				else if (board.at(i).at(j) == Player::black)
				{
					filledCircleRGBA(renderer, x, y, 20, 0, 0, 0, 255);
				}
				else
				{
					filledCircleRGBA(renderer, x, y, 20, 150, 150, 150, 255);
				}
				x += 60;
			}
			x = 190;
			y += 60;
		}
	}

	void Game::renderTopText(SDL_Renderer*& renderer, SDL_Window*& window, TTF_Font*& font, std::string textContent, SDL_Color color)
	{

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textContent.c_str(), color);
		if (textSurface != nullptr)
		{
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (textTexture != nullptr)
			{
				//rendered text position. the box you put the text in
				SDL_Rect textRect{ 300, 10, textSurface->w, textSurface->h };
				//render the text
				//render copy cause you copy the text from the texture to the rect
				//the nullptr means "i want the whole texture copied"
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_DestroyTexture(textTexture);
			}
			else
			{
				std::cerr << "SDL Text Texture Error: " << SDL_GetError() << std::endl;
			}
			SDL_FreeSurface(textSurface);

		}
		else
		{
			std::cerr << "SDL Text Surface Error: " << SDL_GetError() << std::endl;
		}
	}

	void Game::renderBottomText(SDL_Renderer*& renderer, SDL_Window*& window, TTF_Font*& font, std::string textContent, SDL_Color color)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textContent.c_str(), color);
		if (textSurface != nullptr)
		{
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (textTexture != nullptr)
			{
				//rendered text position. the box you put the text in
				SDL_Rect textRect{ 300, 560, textSurface->w, textSurface->h };
				//render the text
				//render copy cause you copy the text from the texture to the rect
				//the nullptr means "i want the whole texture copied"
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_DestroyTexture(textTexture);
			}
			else
			{
				std::cerr << "SDL Text Texture Error: " << SDL_GetError() << std::endl;
			}
			SDL_FreeSurface(textSurface);

		}
		else
		{
			std::cerr << "SDL Text Surface Error: " << SDL_GetError() << std::endl;
		}
	}

	void Game::renderWinScreen(SDL_Renderer*& renderer, SDL_Window*& window, TTF_Font*& font, std::string textContent, SDL_Color color)
	{
		SDL_Rect winBack{ 200,200,300,200 };
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
		SDL_RenderFillRect(renderer, &winBack);

		std::string winningPlayer{};
		if (whiteCount > blackCount)
		{
			winningPlayer = "Winner: White";
		}
		else if (whiteCount < blackCount)
		{
			winningPlayer = "Winner: Black";
		}
		else if (whiteCount == blackCount)
		{
			winningPlayer = "Tie";
		}
		else
		{
			winningPlayer = " ";
		}
		
		SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, winningPlayer.c_str(), color, 300);
		if (textSurface != nullptr)
		{
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (textTexture != nullptr)
			{
				//rendered text position. the box you put the text in
				SDL_Rect textRect{ 200, 200, 300,200 };
				//render the text
				//render copy cause you copy the text from the texture to the rect
				//the nullptr means "i want the whole texture copied"
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_DestroyTexture(textTexture);
			}
			else
			{
				std::cerr << "SDL Text Texture Error: " << SDL_GetError() << std::endl;
			}
			SDL_FreeSurface(textSurface);

		}
		else
		{
			std::cerr << "SDL Text Surface Error: " << SDL_GetError() << std::endl;
		}

		

	}

	Position Game::buttonPressed(int mouseX, int mouseY)
	{
		Position buttonPos{};
		int x{ 165 };
		int y{ 65 };
		int xmin{ 165 };
		int xmax = xmin + 50;
		int ymin{ 65 };
		int ymax = ymin + 50;
		for (int i{ 0 }; i < 8; i++)
		{
			for (int j{ 0 }; j < 8; j++)
			{	
				if (mouseX > xmin && mouseX < xmax && mouseY > ymin && mouseY < ymax)
				{
					return buttonPos;
				}
				buttonPos.column++;
				x += 60;
				xmin = x;
				xmax = xmin + 50;
			}
			buttonPos.row++;
			buttonPos.column = 0;
			x = 165;
			xmin = x;
			xmax = xmin + 50;
			y += 60;
			ymin = y;
			ymax = ymin + 50;
		}
		return { 0,0 };
	}

	std::vector<MoveInfo> Game::getwhiteLegalMoveList()
	{
		return whiteLegalMoveList;
	}

	std::vector<MoveInfo> Game::getblackLegalMoveList()
	{
		return blackLegalMoveList;
	}

	void Game::setStatus(GameStatus status)
	{
		gameStatus = status;
	}
