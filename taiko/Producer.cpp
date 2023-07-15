#include <windows.h>
#include "Producer.h"

Producer::Producer()
{
}

Producer::Producer(SDL_Renderer* renderer)
{

	page = 2;
	const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";

	// page2:
	page2 = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/page1_bg.png");
	Uint16 txt2_1[] = { L'歌', L'曲', 0 };
	Uint16 txt2_2[] = { L'歌', L'曲', L'名', L'稱', 0 };
	Uint16 txt2_3[] = { L'歌', L'曲', L'速', L'度', L' ', L'B', L'P', L'M', 0 };
	text2_1 = Text(txt2_1, fontPath, 100, { 0, 0, 0 }, renderer, { 50, 100 });
	text2_2 = Text(txt2_2, fontPath, 50, { 0, 0, 0 }, renderer, { 50, 270 });
	Text text2_3 = Text(" ", fontPath, 50, { 255, 255, 255 }, renderer, { 55, 400 });
	text2_4 = Text(txt2_3, fontPath, 50, { 0, 0, 0 }, renderer, { 50, 510 });
	Text text2_5 = Text(" ", fontPath, 50, { 255, 255, 255 }, renderer, { 55, 630 });
	textfield2_1 = Button(renderer, 50, 390, 1000, 70);
	prompt2_1 = TextInput(text2_3);
	prompt2_1.setSelect(true);
	textfield2_2 = Button(renderer, 50, 620, 1000, 70);
	prompt2_2 = TextInput(text2_5);
	prompt2_2.setSelect(false);
	prompt2_2.setNum();
	btn2_1 = Button(renderer, 1500, 900, 200, 70, "next", 30, { 0, 0, 0 });
	btn2_1.setStroke(5, 0, 0, 0);
	btn2_1.setCorner(5);
	btn2_1.setEnlarge(true);

	qua_Tri = 4;
	selectboxQua = SelectBox(renderer, 350, 800);
	selectboxQua.setEnable(true);
	selectboxTri = SelectBox(renderer, 650, 800);
	selectboxTri.setEnable(false);
	text2_9 = Text("4/4", fontPath, 60, { 0, 0, 0 }, renderer, { 200, 800 });
	text2_10 = Text("3/4", fontPath, 60, { 0, 0, 0 }, renderer, { 500, 800 });

	// page3:
	dsp = DSP();
	page3 = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/page1_bg.png");
	wavPane1 = Pane(renderer, 0, 50, 1920, 220);
	wavPane2 = Button(renderer, 0, 60, 1920, 200);

	Uint16 txt3_1[] = { L'托', L'曳', L' ', L'.', L'w', L'a', L'v', L'進', L'入', L'視', L'窗', 0 };
	text3_1 = Text(txt3_1, fontPath, 100, { 0, 0, 0 }, renderer, { 500, 350 });

	waveOffset = 0;

	// page4:
	page4 = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/page1_bg.png");
	Uint16 txt4_1[] = { L'點', L'選', L'波', L'型', L'設', L'定', L'起', L'始', L'位', L'置', 0 };
	text4_1 = Text(txt4_1, fontPath, 100, { 0, 0, 0 }, renderer, { 500, 350 });
	Uint16 txt4_2[] = { L'歌', L'曲', L'總', L'長', L'度', 0 };
	text4_2 = Text(txt4_2, fontPath, 60, { 0, 0, 0 }, renderer, { 800, 500 });
	text4_3 = Text("0:00:00", fontPath, 50, { 0, 0, 0 }, renderer, { 820, 600 });
	Uint16 txt4_4[] = { L'作', L'曲', L'起', L'始', L'位', L'置', 0 };
	text4_4 = Text(txt4_4, fontPath, 60, { 0, 0, 0 }, renderer, { 750, 700 });
	text4_5 = Text("0:00:00", fontPath, 50, { 255, 0, 0 }, renderer, { 820, 800 });
	btn4_1 = Button(renderer, 1500, 900, 200, 70, "next", 30, { 0, 0, 0 });
	btn4_1.setStroke(5, 0, 0, 0);
	btn4_1.setCorner(5);
	btn4_1.setEnlarge(true);

	// page5:
	waiting = Text("Fast Fourier Transform processing..,", fontPath, 50, { 0, 0, 0 }, renderer, { 500, 510 });
	page5 = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/page1_bg.png");
	btnAUTO = Button(renderer, 200, 500, 200, 70, "auto", 30, { 0, 0, 0 });
	btnAUTO.setStroke(5, 0, 0, 0);
	btnAUTO.setCorner(5);
	btnAUTO.setEnlarge(true);

	selectboxRed = SelectBox(renderer, 300, 330);
	selectboxRed.setEnable(true);
	selectboxBlue = SelectBox(renderer, 500, 330);
	selectboxBlue.setEnable(false);
	selectboxOrange = SelectBox(renderer, 900, 330);
	selectboxOrange.setEnable(false);
	currentColor = 1;

	selectboxSmall = SelectBox(renderer, 1280, 330);
	selectboxSmall.setEnable(true);
	selectboxBig = SelectBox(renderer, 1480, 330);
	selectboxBig.setEnable(false);
	currentSize = false;

	rangeDiv = Button(renderer, 1170, 950, 600, 80);
	rangeDiv.setStroke(5, 0, 0, 0);
	rangeDiv.setCorner(30);
	Uint16 txtDiv[] = { L'節', L'拍', L'劃', L'分', L' ', L'1', L'/', L'4', 0 };
	textDiv = Text(txtDiv, fontPath, 50, { 255, 255, 255 }, renderer, { 1200, 967 });

	compose1 = Pane(renderer, 0, 600, 1920, 320);
	compose2 = Button(renderer, 0, 610, 1920, 300);

	saveBtn = Button(renderer, 200, 980, 200, 70, "SAVE", 30, { 0, 0, 0 });
	saveBtn.setStroke(5, 0, 0, 0);
	saveBtn.setCorner(5);
	saveBtn.setEnlarge(true);

	//question mark
	questionmark = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/questionmark.png");
	questionBtn = Button(renderer, 1700, 300, 200, 200);
	teaching = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/producer-teaching.png");
	isteaching = false;
}

void Producer::control(Input& inputs, int& scene)
{

	switch (page)
	{
	case 2:
		if (textfield2_1.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			prompt2_1.setSelect(true);
			prompt2_2.setSelect(false);
		}

		if (textfield2_2.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			prompt2_2.setSelect(true);
			prompt2_1.setSelect(false);
		}

		if (selectboxQua.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			qua_Tri = 4;
			selectboxQua.setEnable(true);
			selectboxTri.setEnable(false);
		}

		if (selectboxTri.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			qua_Tri = 3;
			selectboxQua.setEnable(false);
			selectboxTri.setEnable(true);
		}

		if (btn2_1.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			songBpm = 0;
			for (int i = 1; i < strlen(prompt2_2.getString()); i++)
			{
				songBpm = songBpm * 10 + (prompt2_2.getString()[i] - '0');
			}
			for (int i = 1; i <= strlen(prompt2_1.getString()); i++)
			{
				name[i - 1] = prompt2_1.getString()[i];
			}
			if (songBpm > 0 && strlen(name) > 0)
			{
				char empty[2] = " ";
				prompt2_1.setText(empty);
				prompt2_2.setText(empty);
				page = 3;
			}
		}

		prompt2_1.edit(inputs);
		prompt2_2.edit(inputs);
		break;

	case 3:
		if (inputs.type == SDL_DROPCOMPLETE)
		{
			if (inputs.dropfiledir[strlen(inputs.dropfiledir) - 4] == '.' &&
				inputs.dropfiledir[strlen(inputs.dropfiledir) - 3] == 'w' &&
				inputs.dropfiledir[strlen(inputs.dropfiledir) - 2] == 'a' &&
				inputs.dropfiledir[strlen(inputs.dropfiledir) - 1] == 'v')
			{
				strcpy_s(filedir, 260, inputs.dropfiledir);
				printf("%s\n", inputs.dropfiledir);
				printf("%s\n", filedir);
				resultingWaveform = dsp.inputFile(filedir);
				inputs.type = 0;
				start = 0;
			}
		}
		if (dsp.isWaveForm())
		{
			page = 4;
			char songlen[20];
			sprintf_s(songlen, 20, "%d:%d:%d", (int)(dsp.getDuration()) / 60,
				(int)(dsp.getDuration()) % 60,
				(int)((dsp.getDuration() - (int)(dsp.getDuration())) * 100));
			text4_3.setString(songlen);
			text4_3.generateTexture();
		}
		break;
	case 4:
		if (wavPane2.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			start = (abs(waveOffset) + inputs.mouse_X) * dsp.getDuration() / 4000;
			char songlen[20];
			sprintf_s(songlen, 20, "%d:%d:%d", ((int)start) / 60,
				((int)start) % 60,
				(int)((start - (int)start) * 100));
			text4_5.setString(songlen);
			text4_5.generateTexture();
		}

		if (inputs.type == SDL_MOUSEWHEEL &&
			inputs.mouse_Y > wavPane2.getDst()->y &&
			inputs.mouse_Y < wavPane2.getDst()->y + wavPane2.getDst()->h &&
			waveOffset + inputs.mouse_Wheel * 10 <= 0 &&
			waveOffset + inputs.mouse_Wheel * 10>-4000 + wavPane2.getDst()->w)
		{
			waveOffset += inputs.mouse_Wheel * 10;
		}

		if (btn4_1.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
		{
			int barNum = (int)((dsp.getDuration() - start) / (60.0 * qua_Tri / songBpm));
			bin = 96 * barNum;
			isThereBeat = new int[bin];
			for (int i = 0; i < bin; i++)
				isThereBeat[i] = false;
			beats = new Beat[bin];
			printf("%d\n", bin);
			position = 0;
			orangemode = false;
			range = (qua_Tri == 4) ? 24 : 32;
			div = 0;
			page = 5;
		}
		break;
	case 5:
		if (dsp.isSpectrumForm() == 1)
		{
			//printf("waiting\n");
		}
		else
		{
			if (dsp.isThreadExist())
			{
				dsp.DetachThread();
				int pitchIndex = 0;
				for (int i = 0; i < bin; i++)
				{
					isThereBeat[i] = false;
					if (qua_Tri == 4 && pitchIndex < dsp.getPitch().size())
					{
						if (i % 24 == 0 && dsp.getPitch()[pitchIndex] != 0)
						{
							isThereBeat[i] = true;
							Beat beat = Beat(compose2.getRenderer(), (dsp.getPitch()[pitchIndex] > 50) ? 2 : 1, false, position, 250);
							beat.setPosition(220, 680);
							beat.setWidth(160);
							beat.setHeight(160);
							beats[i] = beat;
							pitchIndex++;
						}
					}
					else if (pitchIndex < dsp.getPitch().size())
					{
						if (i % 32 == 0 && dsp.getPitch()[pitchIndex] != 0)
						{
							isThereBeat[i] = true;
							Beat beat = Beat(compose2.getRenderer(), (dsp.getPitch()[pitchIndex] > 50) ? 2 : 1, false, position, 250);
							beat.setPosition(220, 680);
							beat.setWidth(160);
							beat.setHeight(160);
							beats[i] = beat;
							pitchIndex++;
						}
					}
				}
			}

			if (inputs.type == SDL_MOUSEWHEEL &&
				inputs.mouse_Y > wavPane2.getDst()->y &&
				inputs.mouse_Y < wavPane2.getDst()->y + wavPane2.getDst()->h &&
				waveOffset + inputs.mouse_Wheel * 10 <= 0 &&
				waveOffset + inputs.mouse_Wheel * 10>-4000 + wavPane2.getDst()->w)
			{
				waveOffset += inputs.mouse_Wheel * 10;
			}

			if (selectboxRed.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y) && !orangemode)
			{
				currentColor = RED;
				selectboxRed.setEnable(true);
				selectboxBlue.setEnable(false);
				selectboxOrange.setEnable(false);
			}

			if (selectboxBlue.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y) && !orangemode)
			{
				currentColor = BLUE;
				selectboxRed.setEnable(false);
				selectboxBlue.setEnable(true);
				selectboxOrange.setEnable(false);
			}

			if (selectboxOrange.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y) && !orangemode)
			{
				currentColor = ORANGE;
				selectboxRed.setEnable(false);
				selectboxBlue.setEnable(false);
				selectboxOrange.setEnable(true);
			}

			if (selectboxBig.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y) && !orangemode)
			{
				currentSize = true;
				selectboxBig.setEnable(true);
				selectboxSmall.setEnable(false);
			}

			if (selectboxSmall.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y) && !orangemode)
			{
				currentSize = false;
				selectboxBig.setEnable(false);
				selectboxSmall.setEnable(true);
			}

			if (inputs.keyboard_LEFT)
			{
				if (orangemode && position - range < orangeStart)
				{

				}
				else
				{
					if (position - range >= 0)
						position -= range;
					else
						position = 0;
					inputs.keyboard_LEFT = 0;

					for (int i = 0; i < bin; i++)
					{
						if (isThereBeat[i])
							beats[i].setX(220 + (i - position) * 14);
					}
				}
			}

			if (inputs.keyboard_RIGHT)
			{
				bool pass = true;
				if (position + range < bin)
				{
					if (orangemode)
						for (int i = 1; i <= range; i++)
						{
							if (isThereBeat[position + i])
							{
								pass = false;
								break;
							}
						}
					if (pass)
						position += range;
				}
				inputs.keyboard_RIGHT = 0;

				for (int i = 0; i < bin; i++)
				{
					if (isThereBeat[i])
						beats[i].setX(220 + (i - position) * 14);
				}
			}

			if (rangeDiv.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
			{
				int first = rangeDiv.getDst()->x + rangeDiv.getDst()->w / 2;
				int gap = rangeDiv.getDst()->w / 7;
				if (inputs.mouse_X >= first && inputs.mouse_X <= first + gap)
				{
					div = 0;
					range = (qua_Tri == 4) ? 24 : 32;
					Uint16 str[] = { L'節', L'拍', L'劃', L'分', L' ', L'1', L'/', L'4', 0 };
					textDiv.setMandarin(str);
					textDiv.generateTexture();
				}
				else if (inputs.mouse_X >= first + gap && inputs.mouse_X <= first + 2 * gap)
				{
					div = 1;
					range = (qua_Tri == 4) ? 12 : 16;
					Uint16 str[] = { L'節', L'拍', L'劃', L'分', L' ', L'1', L'/', L'8', 0 };
					textDiv.setMandarin(str);
					textDiv.generateTexture();
				}
				else if (inputs.mouse_X >= first + 2 * gap && inputs.mouse_X <= first + 3 * gap)
				{
					div = 2;
					range = (qua_Tri == 4) ? 6 : 8;
					Uint16 str[] = { L'節', L'拍', L'劃', L'分', L' ', L'1', L'/', L'1', L'6', 0 };
					textDiv.setMandarin(str);
					textDiv.generateTexture();
				}

			}

			if (compose2.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
			{
				if (isThereBeat[position])
				{
					if (beats[position].getColor() == ORANGE)
					{
						bool orangeON = false;
						int orangefdex = 0;
						for (int i = 0; i < bin; i++)
						{
							if (isThereBeat[i] && beats[i].getColor() == ORANGE && !orangeON)
							{
								orangeON = true;
								orangefdex = i;
								if (i == position)
								{
									isThereBeat[i] = false;
									for (int j = i; j < bin; j++)
									{
										if (isThereBeat[j] && beats[j].getColor() == ORANGE)
										{
											isThereBeat[j] = false;
											break;
										}
									}
									break;
								}
							}
							else if (i == position && orangeON)
							{
								isThereBeat[orangefdex] = false;
								isThereBeat[i] = false;
								break;
							}
							else if (isThereBeat[i] && beats[i].getColor() == ORANGE && orangeON)
							{
								orangeON = false;
							}
						}
					}
					else
					{
						isThereBeat[position] = false;
						orangemode = false;
					}
				}
				else
				{
					bool orangeON = false;
					bool gotIt = false;
					int orangefdex = 0;
					if (!orangemode)
						for (int i = 0; i < bin; i++)
						{
							if (isThereBeat[i] && beats[i].getColor() == ORANGE && !orangeON)
							{
								orangeON = true;
								orangefdex = i;
							}
							else if (isThereBeat[i] && beats[i].getColor() == ORANGE && orangeON)
							{
								orangeON = false;
							}

							if (i == position && orangeON)
							{
								gotIt = true;
								isThereBeat[orangefdex] = false;
							}

							if (gotIt && isThereBeat[i] && beats[i].getColor() == ORANGE)
							{
								isThereBeat[i] = false;
								break;
							}
						}
					if (!gotIt)
					{
						if (currentColor == ORANGE && !orangemode)
						{
							orangemode = true;
							isThereBeat[position] = true;
							Beat beat = Beat(compose2.getRenderer(), currentColor, currentSize, position, 250);
							beat.setPosition(220, 680);
							beat.setWidth(160);
							beat.setHeight(160);
							beats[position] = beat;
							orangeStart = position;
						}
						else if (currentColor == ORANGE && orangemode)
						{
							orangemode = false;
							isThereBeat[position] = true;
							Beat beat = Beat(compose2.getRenderer(), currentColor, currentSize, position, 250);
							beat.setPosition(220, 680);
							beat.setWidth(160);
							beat.setHeight(160);
							beats[position] = beat;
							beats[orangeStart].setOrangeLen(position - orangeStart);
						}
						else
						{
							isThereBeat[position] = true;
							Beat beat = Beat(compose2.getRenderer(), currentColor, currentSize, position, 250);
							beat.setPosition(220, 680);
							beat.setWidth(160);
							beat.setHeight(160);
							beats[position] = beat;
						}
					}

				}
			}

			if (saveBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
			{
				saveData();
				scene = 0;
			}

			if (dsp.isSpectrumForm() == 0)
			{
				if (btnAUTO.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
				{
					dsp.tuner(true, songBpm, start);
				}
			}
			else if (dsp.isSpectrumForm() == 2)
			{
				if (inputs.mouse_X >= btnAUTO.getDst()->x &&
					inputs.mouse_Y >= btnAUTO.getDst()->y &&
					inputs.mouse_X < btnAUTO.getDst()->x + btnAUTO.getDst()->w &&
					inputs.mouse_Y < btnAUTO.getDst()->y + btnAUTO.getDst()->h)
				{
					graphspect = true;
				}
				else
				{
					graphspect = false;
				}
			}


			if (questionBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y)) {
				if (isteaching == true) {
					//teaching.close();
					isteaching = false;
				}
				else if (isteaching == false) {
					isteaching = true;
				}
			}
		}

		break;
	}

}

void Producer::draw(SDL_Renderer* renderer)
{
	switch (page)
	{
	case 2:
		page2.draw();
		text2_1.draw();
		text2_2.draw();
		textfield2_1.draw(0, 0, 0);
		prompt2_1.draw();
		text2_4.draw();
		textfield2_2.draw(0, 0, 0);
		prompt2_2.draw();
		btn2_1.draw(255, 50, 50);
		selectboxQua.draw();
		selectboxTri.draw();
		text2_9.draw();
		text2_10.draw();
		break;
	case 3:
		page3.draw();
		wavPane1.draw(0, 0, 0);
		wavPane2.draw(50, 50, 100);
		text3_1.draw();
		break;
	case 4:
		page4.draw();
		text4_1.draw();
		text4_2.draw();
		text4_3.draw();
		text4_4.draw();
		text4_5.draw();
		wavPane1.draw(0, 0, 0);
		wavPane2.draw(50, 50, 100);
		btn4_1.draw(255, 0, 0);
		if (true)
		{
			int y = 60;
			int height = 200;
			wavPane1.modify(y, height);
			for (int i = 0; i < 1000; i++) {

				int value = (int)(resultingWaveform[i] * height);
				int y1 = (height - 2 * value) / 2;
				int y2 = y1 + 2 * value;
				roundedRectangleRGBA(renderer, i * 4 + waveOffset, y1 + y, i * 4 + 4 + waveOffset, y2 + y,
					2, 255, 255, 255, 255);
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
			SDL_RenderDrawLine(renderer, (int)(4000 * start / dsp.getDuration() + waveOffset), y, (int)(4000 * start / dsp.getDuration() + waveOffset), y + height);
		}
		break;
	case 5:
		page5.draw();
		saveBtn.draw(255, 0, 0);
		rangeDiv.draw(130, 0, 130);
		textDiv.draw();
		btnAUTO.draw(255, 0, 0);
		//questionBtn.draw(255, 255, 255);
		questionmark.draw();

		if (true)
		{
			int gap = rangeDiv.getDst()->w / 7;
			hlineRGBA(renderer, rangeDiv.getDst()->x + 9 * rangeDiv.getDst()->w / 14,
				rangeDiv.getDst()->x + 13 * rangeDiv.getDst()->w / 14,
				rangeDiv.getDst()->y + rangeDiv.getDst()->h / 2,
				255, 255, 255, 255);
			filledCircleRGBA(renderer,
				rangeDiv.getDst()->x + 9 * rangeDiv.getDst()->w / 14 + div * gap,
				rangeDiv.getDst()->y + rangeDiv.getDst()->h / 2,
				rangeDiv.getDst()->h / 6, 255, 255, 255, 180);
		}

		if (true)
		{
			int xr = 230, xb = 430, xo = 630, yy = 350, ri = 25, ro = 8;
			rangeDiv.modify(xr, xb);
			rangeDiv.modify(xo, yy);
			rangeDiv.modify(ri, ro);
			filledCircleRGBA(renderer, xr, yy, ri + ro, 0, 0, 0, 255);
			filledCircleRGBA(renderer, xr, yy, ri, 241, 85, 45, 255);
			filledCircleRGBA(renderer, xb, yy, ri + ro, 0, 0, 0, 255);
			filledCircleRGBA(renderer, xb, yy, ri, 101, 190, 188, 255);
			roundedBoxRGBA(renderer, xo - ri - ro, yy - ri - ro, xo + 10 * ri + ro - ri, yy + 2 * ri + ro - ri, ri + ro, 0, 0, 0, 255);
			roundedBoxRGBA(renderer, xo - ri, yy - ri, xo + 10 * ri - ri, yy + 2 * ri - ri, ri, 255, 153, 0, 255);

			int xbig = 1400, xsmall = 1200, rb = 35;
			rangeDiv.modify(xbig, xsmall);
			rangeDiv.modify(xr, rb);
			filledCircleRGBA(renderer, xsmall, yy, ri + ro, 0, 0, 0, 255);
			filledCircleRGBA(renderer, xsmall, yy, ri, 255, 255, 255, 255);
			filledCircleRGBA(renderer, xbig, yy, rb + ro, 0, 0, 0, 255);
			filledCircleRGBA(renderer, xbig, yy, rb, 255, 255, 255, 255);
		}

		if (true)
		{
			compose1.draw(0, 0, 0);
			compose2.draw(100, 100, 100);
			int xc = 300, yc = 760, rci = 50, rco = 70, rcc = 40, useless = 0;
			rangeDiv.modify(xc, yc);
			rangeDiv.modify(rci, rco);
			rangeDiv.modify(rcc, useless);
			filledCircleRGBA(renderer, xc, yc, rcc, 150, 150, 150, 255);
			circleRGBA(renderer, xc, yc, rci, 200, 200, 200, 255);
			circleRGBA(renderer, xc, yc, rco, 255, 255, 255, 255);
			for (int i = bin - 1; i >= 0; i--)
			{
				if (i % 96 == 0)
				{
					xc = 300 + (i - position) * 14;
					rangeDiv.modify(xc, useless);
					vlineRGBA(renderer, xc,
						compose2.getDst()->y,
						compose2.getDst()->y + compose2.getDst()->h,
						255, 255, 255, 255);
				}
				if (isThereBeat[i])
					beats[i].draw();
			}
		}

		selectboxRed.draw();
		selectboxBlue.draw();
		selectboxOrange.draw();

		selectboxBig.draw();
		selectboxSmall.draw();

		if (true)
		{
			wavPane1.draw(0, 0, 0);
			wavPane2.draw(50, 50, 100);
			int y = 60;
			int height = 200;
			wavPane1.modify(y, height);
			for (int i = 0; i < 1000; i++) {

				int value = (int)(resultingWaveform[i] * height);
				int y1 = (height - 2 * value) / 2;
				int y2 = y1 + 2 * value;
				roundedRectangleRGBA(renderer, i * 4 + waveOffset, y1 + y, i * 4 + 4 + waveOffset, y2 + y,
					2, 255, 255, 255, 255);
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
			double startpos = 4000 * start / dsp.getDuration();
			SDL_RenderDrawLine(renderer, (int)(startpos + waveOffset), y, (int)(startpos + waveOffset), y + height);
			double gapPerBin = 4000.0 * 4 * 60 / (songBpm * dsp.getDuration() * 96);
			int yy = wavPane2.getDst()->y;
			int hh = wavPane2.getDst()->h;
			for (int i = 0; i <= bin; i += range)
			{
				if (qua_Tri == 4)
				{
					if (i % 96 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 20, yy + hh,
							255, 255, 255, 255);
					}
					else if (i % 24 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 10, yy + hh,
							255, 0, 0, 255);
					}
					else if (i % 12 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 5, yy + hh,
							0, 255, 0, 255);
					}
					else if (i % 6 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 2, yy + hh,
							0, 0, 255, 255);
					}
				}
				else
				{
					if (i % 96 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 20, yy + hh,
							255, 255, 255, 255);
					}
					else if (i % 32 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 10, yy + hh,
							255, 0, 0, 255);
					}
					else if (i % 16 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 5, yy + hh,
							0, 255, 0, 255);
					}
					else if (i % 8 == 0) {
						vlineRGBA(renderer, (int)(startpos + i * gapPerBin + waveOffset),
							yy + hh - 2, yy + hh,
							0, 0, 255, 255);
					}
				}
			}
			for (int i = 0; i <= bin; i++)
			{
				if (i == position)
				{
					boxRGBA(renderer,
						(int)(startpos + i * gapPerBin + waveOffset), yy,
						(int)(startpos + (i + 96) * gapPerBin + waveOffset),
						yy + hh, 255, 255, 255, 100);
					//break;
				}
			}
		}


		if (dsp.isSpectrumForm() == 1)
		{
			boxRGBA(renderer, 0, 0, 1920, 1080, 255, 255, 255, 100);
			waiting.draw();
		}
		if (graphspect && dsp.isSpectrumForm() == 2)
		{
			dsp.drawSpectrum(renderer);
		}
		break;
	}

	if (isteaching == true) {
		teaching.draw();
	}

}

void Producer::saveData()
{
	TCHAR szDir[MAX_PATH];
	swprintf(szDir, MAX_PATH, L"..\\data\\%hs", name);
	if (!CreateDirectory(szDir, NULL))
	{
		printf("create folder failed\n");
	}
	swprintf(szDir, MAX_PATH, L"..\\playerData\\%hs", name);
	if (!CreateDirectory(szDir, NULL))
	{
		printf("create folder failed\n");
	}
	else
	{
		char out[MAX_PATH];
		char txt[MAX_PATH];
		sprintf_s(out, MAX_PATH, "..\\data\\%s\\song.wav", name);
		sprintf_s(txt, MAX_PATH, "..\\data\\%s\\data.txt", name);
		printf("name: %s\n", out);

		FILE* infd, * outfd, * txtfd;
		if (fopen_s(&infd, filedir, "rb"))
		{
			printf("Failed to open input file.\n");
		}
		else if (fopen_s(&outfd, out, "wb"))
		{
			printf("Failed to open output file.\n");
		}
		else if (fopen_s(&txtfd, txt, "w"))
		{
			printf("Failed to open txt file.\n");
		}
		else
		{
			const int len = 4096;
			char buf[4096];
			while (1)
			{

				if (feof(infd))

					break;

				int nBytesRead = (int)fread(buf, 1, len, infd);

				if (nBytesRead <= 0)

					break;

				fwrite(buf, 1, nBytesRead, outfd);
			}
			fclose(infd);
			fclose(outfd);

			fprintf_s(txtfd, "Track name :\n%s\n\n", name);
			fprintf_s(txtfd, "Artist :\n%s\n\n", name);
			fprintf_s(txtfd, "BPM :\n%d\n\n", (int)songBpm);
			fprintf_s(txtfd, "Start Duration :\n%lf\n\n", start * 1000);
			int arrlen = 0;
			for (int i = 0; i < bin; i++)
				if (isThereBeat[i])
					arrlen++;
			fprintf_s(txtfd, "array length :\n%d\n\n", arrlen);
			double gap = 4 * 60.0 * 1000 / (songBpm * 96);
			for (int i = 0; i < bin; i++)
			{
				if (isThereBeat[i])
				{
					fprintf_s(txtfd, "Beat no.\n%d\n", i);
					fprintf_s(txtfd, "Property :\n%d\n", beats[i].getColor());
					fprintf_s(txtfd, "Size :\n%s\n", (beats[i].getSize()) ? "true" : "false");
					fprintf_s(txtfd, "Duration :\n%lf\n\n\n", start * 1000 + i * gap);
				}
			}
			fclose(txtfd);
		}
	}


	page = 2;

	const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
	char empty[] = " ";
	prompt2_1.setText(empty);
	prompt2_1.generateTexture();
	prompt2_1.setSelect(true);
	prompt2_2.setText(empty);
	prompt2_2.generateTexture();
	prompt2_2.setSelect(false);


	qua_Tri = 4;
	selectboxQua.setEnable(true);
	selectboxTri.setEnable(false);

	dsp = DSP();


	waveOffset = 0;


	selectboxRed.setEnable(true);
	selectboxBlue.setEnable(false);
	selectboxOrange.setEnable(false);
	currentColor = 1;

	selectboxSmall.setEnable(true);
	selectboxSmall.setEnable(false);
	currentSize = false;
	isteaching = false;

}