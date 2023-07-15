#pragma once
#include "GameCtrl.h"
#include "Pane.h"
#include "Button.h"
#include "Text.h"
#include "Input.h"
#include "SDL_ttf.h"
#include "TextInput.h"
class ScoreCtrl : public GameCtrl
{
public:
	ScoreCtrl();
	ScoreCtrl(SDL_Renderer* renderer, GameCtrl p);
	void control(SDL_Renderer* renderer, Input& inputs, int& gameState);
	void readOldFile();
	void writeFile();
	void draw(SDL_Renderer* renderer);
	void changIntToConst();
	virtual void close();
private:
	Pane crown;
	Pane flower;
	Pane people_all;
	Pane people_m;
	Pane people_f;
	bool people;

	Button playerchoose, playername, record, rank;

	Text player, log, name;
	TextInput tin;

	GameCtrl gctrl;
	const char* playerName;
protected:
	Pane bg;
	int songname;
	const char* totalbadtext;
	const char* totaloktext;
	const char* totalgoodtext;
	const char* combotext;
	const char* lastcombotext;
	const char* scoretext;
	const char* songnametext;
	const char* score;
	const char* fontPath;

	// Uint16* totalbadtext;
	Text nameText;
	Text scoreText;
	Text badText, okText, goodText;
	Text comboText, mostcomboText, pointText;

	Pane statusgood;
	Pane statusok;
	Pane statusbad;
	Pane mostcombo;
	Pane Combo;

	Button exitBtn;
	int p, flag, re;
	int last_point, last_song;
	char s[40]; // store file name + location
};
