#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

enum Player
{
	empty,
	white,
	black
};

enum GameStatus
{
	ongoing,
	finished,
};

struct Position
{
	int row{};
	int column{};
};

struct MoveInfo
{
	Player moverPlayer{};
	Position position{};
	std::vector<Position> convertablePieces{};
};

int intInputValid();

int moveValidator();


class Game
{
private:
	std::array <std::array<Player, 8>, 8> board{};
	int whiteCount{ 2 };
	int blackCount{ 2 };
	Player currentPlayer{ Player::black };
	GameStatus gameStatus{ ongoing };
	Player winner{ Player::empty };
	std::vector<MoveInfo> whiteLegalMoveList{};
	std::vector<MoveInfo> blackLegalMoveList{};
	SDL_Rect boardBack{ 150,50,500,500 };
	SDL_Rect boardBorder{ 145,45,510,510 };
	

public:
	Game();

	//initializes board
	//had trouble initializing it correctly in constructor so copied from prev ver
	void makeBoard();

	Player getOpponent(Player player);


	//check if its inside the board still
	bool isInsideBoard(int row, int column);


	//find pieces that can be converted in a direction depending on offset, return list
	//should only be passed empty spaces
	std::vector<Position> convertedPieces(Position position, Player player, int rowOffset, int columnOffset);

	//returns list of valid convertable spots for all directions
	std::vector<Position> checkDirections(Position position, Player player);

	//returns true if the move is legal, false if it is not
	bool canPieceMove(Position movePosition, Player player);

	void setLegalMoves(Player player);

	void setColorCounts();

	void convertPieces(std::vector<Position> convertPositions);

	void makeMove(Position position);



	void play(Position pos);

	void checkBoardFullness();

	GameStatus getStatus();

	Player getCurrentPlayer();

	void setCurrentPlayer(Player player);

	void setTurn(Player nextPlayer);

	Player checkWinner();

	void renderBoard(SDL_Renderer*& renderer);

	void renderPieces(SDL_Renderer*& renderer);

	void renderTopText(SDL_Renderer*& renderer, SDL_Window*& window,  TTF_Font*& font, std::string textContent, SDL_Color color);

	void renderBottomText(SDL_Renderer*& renderer, SDL_Window*& window, TTF_Font*& font, std::string textContent, SDL_Color color);

	void renderWinScreen(SDL_Renderer*& renderer, SDL_Window*& window, TTF_Font*& font, std::string textContent, SDL_Color color);

	Position buttonPressed(int mouseX, int mouseY);

	std::vector<MoveInfo> getwhiteLegalMoveList();

	std::vector<MoveInfo> getblackLegalMoveList();

	void setStatus(GameStatus status);
};