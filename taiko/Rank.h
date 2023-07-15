#pragma once
#include "ScoreCtrl.h"
#include "Pane.h"
#include "Button.h"
#include "Text.h"
#include "Input.h"
#include "SDL_ttf.h"

class Rank : public ScoreCtrl
{
public:
	Rank();
	Rank(SDL_Renderer* renderer);

	void draw(SDL_Renderer* renderer);
	void control(SDL_Renderer* renderer, Input& inputs, int& gameState);
	void playerRank();
	void RankScore(SDL_Renderer* renderer);
	void Readtxt(SDL_Renderer* renderer, int r);

protected:
	int txtNum;
	int* playerScore;
	int** scorerank;
	char** playerPath;
	char** playerName;
private:
	Button* txtName;
	Text title, * ranking;
	int pushbutton;

};

