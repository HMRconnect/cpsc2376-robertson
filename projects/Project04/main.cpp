#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include "game.h"


int main()
{
	Game othello{};
	othello.setLegalMoves(Player::black);
	othello.setLegalMoves(Player::white);
	othello.makeBoard();
	othello.printRules();
	while (othello.getStatus() == ongoing)
	{
		othello.printBoard();
		othello.setTurn(Player::white);
		othello.play();
		if (othello.getStatus() == finished)
		{
			break;
		}
		othello.checkBoardFullness();
		if (othello.getStatus() == finished)
		{
			break;
		}

		othello.printBoard();
		othello.setTurn(Player::black);
		othello.play();
		if (othello.getStatus() == finished)
		{
			break;
		}
		othello.checkBoardFullness();
		if (othello.getStatus() == finished)
		{
			break;
		}
	}
	othello.checkWinner();
	return 0;
}