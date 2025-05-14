#define SDL_MAIN_HANDLED
#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void renderRules(SDL_Renderer*& renderer, SDL_Window*& window, TTF_Font*& font)
{
	SDL_Color black{ 0,0,0,255 };
	std::string textContent = "Rules: take turns selecting a spot to place a tile and convert any tiles between to your color! The one who controls the most tiles wins! Press E to continue.";
	SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, textContent.c_str(), black, 600);
	if (textSurface != nullptr)
	{
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textTexture != nullptr)
		{
			//rendered text position. the box you put the text in
			SDL_Rect rulesBoard{ 50, 100, 700, 400 };
			//render the text
			//render copy cause you copy the text from the texture to the rect
			//the nullptr means "i want the whole texture copied"
			SDL_RenderCopy(renderer, textTexture, nullptr, &rulesBoard);
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

int main()
{
	//create/prepare game object
	Game othello{};
	othello.setLegalMoves(Player::black);
	othello.setLegalMoves(Player::white);
	othello.makeBoard();

	//initialize SDL stuff
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Othello",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (!window)
	{
		std::cerr << "SDL Window Creation Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		TTF_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "SDL Renderer Creation Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		TTF_Quit();
		return 1;
	}

	TTF_Font* font = TTF_OpenFont("IBMPlexSerif-Medium.ttf", 24);
	if (!font)
	{
		std::cerr << "SDL Renderer Creation Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		TTF_Quit();
		return 1;
	}
	
	bool rulesShown = true;
	SDL_Rect rulesBoard{ 50, 100, 700, 400 };

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0,0,0,255 };
	bool illegalMove = false;

	bool running = true;
	SDL_Event e;
	othello.setCurrentPlayer(Player::white);

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running = false;
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				running = false;
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e && rulesShown)
			{
				rulesShown = false;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				Position pos = othello.buttonPressed(e.button.x, e.button.y);
				othello.setLegalMoves(Player::black);
				othello.setLegalMoves(Player::white);
				if (othello.getwhiteLegalMoveList().size() == 0 && othello.getblackLegalMoveList().size() == 0)
				{
					std::cout << "There are no more legal moves remaining!" << std::endl;
					othello.setStatus(finished);
					break;
				}
				if (othello.getCurrentPlayer() == Player::white)
				{
					if (othello.getwhiteLegalMoveList().size() == 0)
					{
						othello.setTurn(othello.getOpponent(othello.getCurrentPlayer()));
						othello.setStatus(finished);
						break;
					}
				}
				if (othello.getCurrentPlayer() == Player::black)
				{
					if (othello.getwhiteLegalMoveList().size() == 0)
					{
						othello.setTurn(othello.getOpponent(othello.getCurrentPlayer()));
						othello.setStatus(finished);
						break;
					}
				}
				if (othello.getStatus() == GameStatus::finished)
				{
					std::cout << "finished";
					break;
				}
				if (othello.canPieceMove(pos, othello.getCurrentPlayer()))
				{
					
					othello.play(pos);
					illegalMove = false;
					othello.setTurn(othello.getOpponent(othello.getCurrentPlayer()));
				}
				else
				{
					illegalMove = true;
				}		
				othello.checkBoardFullness();
				if (othello.getStatus() == finished)
				{
					break;
				}

			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r && rulesShown)
			{
				othello = Game{};
			}
		}
		SDL_SetRenderDrawColor(renderer, 115, 77, 20, 255);
		SDL_RenderClear(renderer);
		othello.renderBoard(renderer);

		othello.renderPieces(renderer);

		if (rulesShown)
		{
			SDL_SetRenderDrawColor(renderer, 133, 105, 64, 255);
			SDL_RenderFillRect(renderer, &rulesBoard);
			renderRules(renderer, window, font);
		}


		if (othello.getCurrentPlayer() == Player::white)
		{
			othello.renderTopText(renderer, window, font, "Player 1's Turn!", white);
		}
		if (othello.getCurrentPlayer() == Player::black)
		{
			othello.renderTopText(renderer, window, font, "Player 2's Turn!", black);
		}

		if (illegalMove == true)
		{
			if (othello.getCurrentPlayer() == Player::white)
			{
				othello.renderBottomText(renderer, window, font, "Illegal move, try again!", white);
			}
			if (othello.getCurrentPlayer() == Player::black)
			{
				othello.renderBottomText(renderer, window, font, "Illegal move, try again!", black);
			}
		}
		if (illegalMove == false)
		{
			othello.renderBottomText(renderer, window, font, " ", black);
		}

		if (othello.getStatus() == finished)
		{			
			othello.renderWinScreen(renderer, window, font, "Game Over!", black);
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(16); // ~60 FPS

	}


	//destruct SDL stuff
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}