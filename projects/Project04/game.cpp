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

	void Game::printRules()
	{
		std::cout << "OTHELLO\n"
			<< "-----------------------------------------------------\n"
			<< "Rules:\n" << "- Players must take turns adding new Player each round, by choosing a space to place it in.\n"
			<< "- Player 1 controls white, Player 2 controls black.\n"
			<< "- Your goal is to convert as many Player to your color as possible, before the board fills up or no more legal moves are possible.\n"
			<< "- You may place a piece such that it creates a vertical, horizontal or diagonal occupied line between it and another of your Player,"
			<< " with the opposing player's Player in the middle.\n"
			<< "- Any of the opposing player's Player between these two Player of yours will be converted to your color.\n"
			<< "- Move position is chosen by entering the desired row and column number.\n"
			<< "Good luck.\n" << "-----------------------------------------------------" << std::endl;
	}

	std::string Game::printPiece(const Player piece)
	{
		if (piece == Player::empty)
		{
			return "0";
		}
		else if (piece == Player::white)
		{
			return "W";
		}
		else if (piece == Player::black)
		{
			return "B";
		}
		else
		{
			return "X"; //Display error indicator
		}
	}

	void Game::printBoard()
	{
		std::cout << "   0   1   2   3   4   5   6   7   \n";
		for (int i{ 0 }; i < board.size(); i++)
		{
			std::cout << i << " ";
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				std::cout << "[" << printPiece(board.at(i).at(j)) << "] ";
			}
			std::cout << "\n";
		}
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

	void Game::play()
	{
		setLegalMoves(Player::black);
		setLegalMoves(Player::white);
		if (whiteLegalMoveList.size() == 0 && blackLegalMoveList.size() == 0)
		{
			std::cout << "There are no more legal moves remaining!" << std::endl;
			gameStatus = finished;
			return;
		}
		if (currentPlayer == Player::white)
		{
			if (whiteLegalMoveList.size() == 0)
			{
				std::cout << "You have no legal moves! Your turn is skipped." << std::endl;
				return;
			}
		}
		if (currentPlayer == Player::black)
		{
			if (whiteLegalMoveList.size() == 0)
			{
				std::cout << "You have no legal moves! Your turn is skipped." << std::endl;
				return;
			}
		}
		while (true)
		{
			std::cout << "-----------------------------------------------\n"
				<< "Player " << currentPlayer << " , it is your turn.\n"
				<< "Where would you like to place your piece?" << std::endl;

			Position nextPiece{};
			std::cout << "Row number:";
			nextPiece.row = moveValidator();
			std::cout << "Column number:";
			nextPiece.column = moveValidator();


			if (canPieceMove(nextPiece, currentPlayer) == true)
			{
				//set selected spot to correct piece
				board.at(nextPiece.row).at(nextPiece.column) = currentPlayer;
				//convert pieces between to correct color
				makeMove(nextPiece);
				//then end the while loop & return to main to reprint the board & call next turn
				return;
			}
			else
			{
				std::cout << "That is not a legal move, please try again." << std::endl;
				continue;
			}
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

	void Game::setTurn(Player nextPlayer)
	{
		currentPlayer = nextPlayer;
	}

	void Game::checkWinner()
	{
		if (whiteCount > blackCount)
		{
			std::cout << "Player 1 is the winner!" << std::endl;

		}
		else if (whiteCount < blackCount)
		{
			std::cout << "Player 2 is the winner" << std::endl;

		}
		else if (whiteCount == blackCount)
		{
			std::cout << "Somehow, it's a tie!" << std::endl;

		}
	}
