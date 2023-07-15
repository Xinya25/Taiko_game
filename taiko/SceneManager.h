#pragma once
#include "Input.h"
#include "Pane.h"
#include "HomeCtrl.h"
#include "MenuCtrl.h"
#include "StartCtrl.h"
#include "GameCtrl.h"
#include "ScoreCtrl.h"
#include "Producer.h"
#include "Rank.h"
#include <SDL.h>
#include <stdio.h>

class SceneManager
{
private:
	Input input;
	Pane cursor;
	SDL_Event event;
	const Uint8* keyboard;

	/*  0: home page
		1: menu
		2: load game
		3: gaming
	*/
	int scene = 10;

	StartCtrl stctrl;
	HomeCtrl hctrl;
	MenuCtrl mctrl;
	GameCtrl gctrl;
	ScoreCtrl sctrl;
	Rank rank;
	Producer producer;

	bool init;
	bool init1;
	bool init3;
	bool init4;
	bool init6;

public:
	SceneManager();
	SceneManager(SDL_Renderer* renderer);
	void manage(SDL_Renderer* renderer, bool& quit);
	void getEvent(SDL_Renderer* renderer, bool& quit);
};
