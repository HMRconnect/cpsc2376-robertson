#include <iostream>
#include <limits>
#include <vector>
#include <array>

enum class Pieces
{
	empty,
	white,
	black,
};

enum GameStatus
{
	ongoing,
	finished,
};

struct PiecePosition
{
	int rowNumber{ 0 };
	int columNumber{ 0 };
};

void printRules()
{
	std::cout << "OTHELLO/n"
		<< "-----------------------------------------------------\n"
		<< "Rules:\n" << "- Players must take turns adding new pieces each round, by choosing a space to place it in.\n"
		<< "- Player 1 controls white, Player 2 controls black.\n"
		<< "- Your goal is to convert as many pieces to your color as possible, before the board fills up or no more legal moves are possible.\n"
		<< "- You may place a piece such that it creates a vertical or horizontal occupied line between it and another of your pieces,"
		<< " with the opposing player's pieces in the middle.\n"
		<< "- Any of the opposing player's pieces between these two pieces of yours will be converted to your color.\n"
		<< "- This version does not allow diagonal lines.\n"
		<< "- Move position is chosen by entering the desired row and column number.\n"
		<< "Good luck.\n" << "-----------------------------------------------------" << std::endl;
}

std::string printPiece(const Pieces piece)
{
	if (piece == Pieces::empty)
	{
		return "0";
	}
	else if (piece == Pieces::white)
	{
		return "W";
	}
	else if (piece == Pieces::black)
	{
		return "B";
	}
	else
	{
		return "X"; //Display error indicator
	}
}

void printBoard(const std::array <std::array<Pieces, 8>, 8>& board)
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


void checkWinner(const std::array <std::array<Pieces, 8>, 8>& board)
{
	std::cout << "The game is finished!" << std::endl;
	int whiteCount{};
	int blackCount{};
	for (int i{ 0 }; i < board.size(); i++)
	{
		for (int j{ 0 }; j < board.at(i).size(); j++)
		{
			if (board.at(i).at(j) == Pieces::white)
			{
				whiteCount++;
			}
			else if (board.at(i).at(j) == Pieces::black)
			{
				blackCount++;
			}
		}
	}
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



//returns vector of pointers to spots that will be converted after a move
std::vector<Pieces*> checkDirections(PiecePosition currentPosition, bool playerTurn, std::array<std::array<Pieces, 8>, 8>& board)
{
	std::vector<Pieces*> convertablePieces{};
	PiecePosition checkingPosition = currentPosition;
	if (playerTurn == 0)
	{
		//up
		checkingPosition.rowNumber++;
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.rowNumber < 8 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{

					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.rowNumber++;
			}
		}
		checkingPosition = currentPosition;
		checkingPosition.rowNumber--;
		//down
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.rowNumber > -1 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{

					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.rowNumber--;
			}
		}
		checkingPosition = currentPosition;
		checkingPosition.columNumber++;
		//right
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.columNumber < 8 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{

					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{

					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.columNumber++;
			}
		}
		checkingPosition = currentPosition;
		checkingPosition.columNumber--;
		//left
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.columNumber > -1 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{

					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.columNumber--;
			}
		}
		checkingPosition = currentPosition;
		return convertablePieces;
	}
	else
	{
		checkingPosition.rowNumber++;
		//up
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.rowNumber < 8 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.rowNumber++;
			}
		}
		checkingPosition = currentPosition;
		checkingPosition.rowNumber--;
		//down
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.rowNumber > -1 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.rowNumber--;
			}
		}
		checkingPosition = currentPosition;
		checkingPosition.columNumber++;
		//right
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.columNumber < 8 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.columNumber++;
			}
		}
		checkingPosition = currentPosition;
		checkingPosition.columNumber--;
		//left
		{
			std::vector<Pieces*> oppPieces{};
			while (checkingPosition.columNumber > -1 && board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) != Pieces::empty)
			{


				if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::white)
				{
					oppPieces.push_back(&board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber));
				}
				else if (board.at(checkingPosition.rowNumber).at(checkingPosition.columNumber) == Pieces::black)
				{
					convertablePieces.insert(convertablePieces.end(), oppPieces.begin(), oppPieces.end());
				}
				checkingPosition.columNumber--;
			}
		}
		checkingPosition = currentPosition;
		return convertablePieces;
	}
}

//returns a vector of pointers to spots it is legal for the player to move pieces to on this turn
std::vector<Pieces*> findLegalMoves(bool playerTurn, std::array <std::array<Pieces, 8>, 8>& board)
{
	std::vector<Pieces*> legalMovesList{};

		for (int i{ 0 }; i < board.size(); i++)
		{
			for (int j{ 0 }; j < board.at(i).size(); j++)
			{
				if (board.at(i).at(j) == Pieces::empty)
				{
					//finds if there are any moves that can be made from this spot
					//this is all very inefficient but i've just accepted that at this point
					PiecePosition currentPossiblePosition{ i,j };
					//should check all directions out from the spot based on whose turn it is
					std::vector<Pieces*> convertablePieces = checkDirections(currentPossiblePosition, playerTurn, board);
					if (convertablePieces.size() != 0)
					{
						legalMovesList.push_back(&board.at(i).at(j));
					}
				}
			}
		}

	return legalMovesList;
}

//pass it the chosen move position
void makeMove(PiecePosition currentPosition, bool playerTurn, std::array<std::array<Pieces, 8>, 8>& board)
{
	std::vector<Pieces*> convertablePieces = checkDirections(currentPosition, playerTurn, board);
	if (playerTurn == 0)
	{
		for (int i{ 0 }; i < convertablePieces.size(); i++)
		{
			*convertablePieces.at(i) = Pieces::white;
		}
	}
	else
	{
		for (int i{ 0 }; i < convertablePieces.size(); i++)
		{
			*convertablePieces.at(i) = Pieces::black;
		}
	}
	
}

//returns true if the move is legal, false if it is not
bool canPieceMove(bool playerTurn, std::array <std::array<Pieces, 8>, 8>& board, PiecePosition nextPiece)
{
	std::vector<Pieces*> legalMovesList = checkDirections(nextPiece, playerTurn, board);
	if (legalMovesList.size() == 0)
	{
		return false;
	}
	return true;
}

bool areThereLegalMoves(bool playerTurn, std::array <std::array<Pieces, 8>, 8>& board)
{
	//get list of legal moves
	std::vector<Pieces*> legalMovesList{ findLegalMoves(playerTurn, board) };
	if (legalMovesList.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//return 0 or 1 based on whether the board is full or not, indicating whether the game continues.
void checkBoardFullness(GameStatus& gameStatus, const std::array <std::array<Pieces, 8>, 8>& board)
{
	for (int i{ 0 }; i < board.size(); i++)
	{
		for (int j{ 0 }; j < board.at(i).size(); j++)
		{
			if (board.at(i).at(j) == Pieces::empty)
			{
				gameStatus = ongoing; // The board is not full, the game continues
				return;
			}
		}
	}
	gameStatus = finished; //each spot has been checked and no space is empty, game is over
} 

//makes board, also functions as reset
void makeBoard(std::array <std::array<Pieces, 8>, 8>& board)
{
	std::array <std::array<Pieces, 8>, 8 > emptyBoard
	{ {
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::white,Pieces::black,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::black,Pieces::white,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,},
		{Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,Pieces::empty,},
	} };
	board = emptyBoard;
}

void play(bool playerTurn, GameStatus& gameStatus, std::array <std::array<Pieces, 8>, 8>& board)
{
	if (playerTurn == 0)
	{
		if ((areThereLegalMoves(0, board) == false) && (areThereLegalMoves(1, board) == false))
		{
			std::cout << "There are no more legal moves remaining!" << std::endl;
			gameStatus = finished;
			return;
		}
		if (areThereLegalMoves(playerTurn, board) == false)
		{
			std::cout << "You have no legal moves! Your turn is skipped." << std::endl;
			return;
		}
		while (true)
		{	
			std::cout << "-----------------------------------------------\n"
				<< "Player 1, it is your turn.\n"
				<< "Where would you like to place your piece?" << std::endl;

			PiecePosition nextPiece{};
			std::cout << "Row number:";
			nextPiece.rowNumber = moveValidator();
			std::cout << "Column number:";
			nextPiece.columNumber = moveValidator();

			bool isMoveLegal = canPieceMove(playerTurn, board, nextPiece);
			if (isMoveLegal == true)
			{
				//set selected spot to correct piece
				board.at(nextPiece.rowNumber).at(nextPiece.columNumber) = Pieces::white;
				//convert pieces between to correct color
				makeMove(nextPiece, playerTurn, board);
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
	else
	{
		if ((areThereLegalMoves(0, board) == false) && (areThereLegalMoves(1, board) == false))
		{
			std::cout << "There are no more legal moves remaining!" << std::endl;
			gameStatus = finished;
			return;
		}
		if (areThereLegalMoves(playerTurn, board) == false)
		{
			std::cout << "You have no legal moves! Your turn is skipped." << std::endl;
			return;
		}
		while (true)
		{
			std::cout << "-----------------------------------------------\n"
				<< "Player 2, it is your turn.\n"
				<< "Where would you like to place your piece?" << std::endl;

			PiecePosition nextPiece{};
			std::cout << "Row number:";
			nextPiece.rowNumber = moveValidator();
			std::cout << "Column number:";
			nextPiece.columNumber = moveValidator();

			bool isMoveLegal = canPieceMove(playerTurn, board, nextPiece);
			if (isMoveLegal == true)
			{
				//set selected spot to correct piece
				board.at(nextPiece.rowNumber).at(nextPiece.columNumber) = Pieces::black;
				//convert pieces between to correct color
				makeMove(nextPiece, playerTurn, board);
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
}

int main()
{
	std::array <std::array<Pieces, 8>, 8> board{};
	GameStatus gameStatus{ ongoing }; 
	bool playerTurn{ 0 }; //0 is p1/white, 1 is p2/black
	makeBoard(board);
	printRules();
	while (gameStatus == ongoing)
	{
		printBoard(board);
		playerTurn = 0; //p1/white turn
		play(playerTurn, gameStatus, board);
		if (gameStatus == finished)
		{
			break;
		}
		checkBoardFullness(gameStatus, board);
		if (gameStatus == finished)
		{
			break;
		}

		printBoard(board);
		playerTurn = 1; //p2/black turn
		play(playerTurn, gameStatus, board);
		checkBoardFullness(gameStatus, board);
		if (gameStatus == finished)
		{
			break;
		}
		checkBoardFullness(gameStatus, board);
		if (gameStatus == finished)
		{
			break;
		}
	}

	checkWinner(board);
	
	return 0;
}