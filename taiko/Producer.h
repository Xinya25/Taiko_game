#pragma once
#include "Pane.h"
#include "Input.h"
#include "Text.h"
#include "TextInput.h"
#include "Button.h"
#include "Beat.h"
#include "DSP.h"
#include "SelectBox.h"
#include "SongData.h"

class Producer : SongData
{
private:
	int page;
	float* resultingWaveform;
	char name[31];
	char filedir[260];
	double songBpm;
	double start;	// millisec
	int qua_Tri;	// 3: Tri, 4: Qua


	// page2:
	Pane page2;
	Text text2_1;
	Text text2_2;

	Text text2_4;
	Button textfield2_1;
	TextInput prompt2_1;
	Button textfield2_2;
	TextInput prompt2_2;
	Button btn2_1;
	SelectBox selectboxQua;
	SelectBox selectboxTri;
	Text text2_9;
	Text text2_10;

	// page3;
	DSP dsp;
	Pane page3;
	Pane wavPane1;
	Button wavPane2;
	int waveOffset;
	Text text3_1;

	// page4:
	Pane page4;
	Text text4_1;
	Text text4_2;
	Text text4_3;
	Text text4_4;
	Text text4_5;
	Button btn4_1;

	// page5:
	Pane page5;
	Text waiting;
	Button btnAUTO;
	SelectBox selectboxRed;
	SelectBox selectboxBlue;
	SelectBox selectboxOrange;
	SelectBox selectboxBig;
	SelectBox selectboxSmall;
	Button rangeDiv;
	Text textDiv;
	int div;
	double now;
	int currentColor;
	bool currentSize;
	int bin;
	int position;
	int range;
	bool graphspect;

	Pane compose1;
	Button compose2;
	Beat* beats;
	int* isThereBeat;
	bool orangemode;
	int orangeStart;

	Button saveBtn;

	SDL_Event event;

	void saveData();

	//question mark
	Button questionBtn;
	Pane questionmark;
	Pane teaching;
	bool isteaching;
public:
	Producer();
	Producer(SDL_Renderer* renderer);
	void control(Input& inputs, int& gameState);
	void draw(SDL_Renderer* renderer);
};

