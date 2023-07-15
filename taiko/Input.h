#pragma once
/*
  Inputs
  Stores the state of the different inputs (keyboard/mouse) for
  the current tick. Updated on each game loop.
*/
class Input
{
private:

public:
	// keyboards, mouseXY, mouseLF...
	bool isEvent;

	int mouse_Right;
	int mouse_Left;
	int mouse_X;
	int mouse_Y;
	int mouse_Wheel;

	int keyboard_Space;
	int keyboard_F;
	int keyboard_D;
	int keyboard_J;
	int keyboard_K;
	int keyboard_Z;
	int keyboard_X;


	int keyboard_LEFT;
	int keyboard_RIGHT;

	int keyboard_Esc;
	int keyboard_F5;

	char keyTyped[32];
	int keySym;


	char dropfiledir[200];

	int type;
	Input();
	// setters, getters

};

