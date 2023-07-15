#pragma once
#include <SDL.h>
#include "Input.h"
#include "Button.h"
#include "Const.h"
#include "Pane.h"
#include "SongData.h"
#include "Sprite.h"
#include "Beat.h"
#include "Text.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

class GameCtrl : public SongData
{
private:
	bool isDon1KeyPressed;
	bool isDon2KeyPressed;
	bool isKa1KeyPressed;
	bool isKa2KeyPressed;
	bool isSongPlayed;

	int startPosition;

	bool* reg;
	int* timer;

	double speed;

	bool* isBeatHit;
	bool* isBeatFly;
	bool* isComboChecked;
	bool* isPointCount;
	//char* Str;

	Pane bgPane1a;
	Pane bgPane1b;
	Pane bgPane2;
	Pane bgPane3;
	Pane scorebg;
	Pane Taiko;
	Pane leftdon;
	Pane rightdon;
	Pane leftka;
	Pane rightka;
	Pane statusPane;

	Sprite firework;
	Sprite doll;
	Sprite surprise1;
	Sprite surprise2;
	Sprite surprise3;
	Sprite surprise4;

	Beat* beats;
	Beat* backupBeats;

	TIME startTime;
	TIME currentTime;

	Text scoreText;
	Text comboText;

	Mix_Music* music;
	Mix_Chunk* donEffect;
	Mix_Chunk* kaEffect;
	Mix_Music* scoremusic;

	void createBackGround(SDL_Renderer* renderer);
	void TaikoAnimation(int x);
	void Timer(int x);
	void setMovingSpeed();
	void createBeats(SDL_Renderer* renderer);
	void donPressed();
	void kaPressed();
	int findClosest(TIME pressTime);
	int checkStatus(int color, int checkColor,
		TIME pressTime, TIME checkTime);
	void checkCombo();
	void showPoint();
	void setText(SDL_Renderer* renderer);
	void countPoint(int status);
	void setPosition();
	void loadAudio(int songnumber);
	void draw(SDL_Renderer* renderer);
	void modify(int& x, int& y);
	void demodify(int& x, int& y);

protected:
	int totalGood;
	int totalOk;
	int totalBad;
	int combo;
	int maxCombo;
	int lastCombo;
	int point;
public:
	GameCtrl();
	GameCtrl(SDL_Renderer* renderer);

	void control(SDL_Renderer* renderer, Input& inputs, int& gameState);
	int i; // song number
	//const char *fontPath;
	const char* scoretext;
	const char* combotext;
	//const char* scoretext;
	int getpoint();
	int getgood();
	int getok();
	int getbad();
	int getcombo();
	int getlastcombo();
	int closemusic(int song);
	int getSong();
	void closegame();
};
