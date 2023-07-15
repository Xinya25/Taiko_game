#include "GameCtrl.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

GameCtrl::GameCtrl() : SongData()
{
}

GameCtrl::GameCtrl(SDL_Renderer* renderer) : SongData()
{
	point = 0;
	combo = 0;
	lastCombo = 0, maxCombo = 0;
	totalBad = 0;
	totalGood = 0;
	totalOk = 0;

	readFile();
	loadAudio(choice);
	createBackGround(renderer);
	reg = new bool[4];
	timer = new int[7];
	setMovingSpeed();
	createBeats(renderer);

	setText(renderer);

	Mix_PlayMusic(music, 1);
	startTime = (TIME)SDL_GetTicks64();
	//cout << "total red and blue = " << redandblue << endl;
}

bool test = true;
void GameCtrl::control(SDL_Renderer* renderer, Input& inputs,
	int& scene)
{
	currentTime = (TIME)SDL_GetTicks64() - startTime;

	if (test)
	{
		doll.startTimer(50);
		surprise1.startTimer(50);
		surprise2.startTimer(50);
		surprise3.startTimer(50);
		surprise4.startTimer(50);
		test = false;
	}

	for (int x = 0; x < sizeof(timer); x++)
	{
		Timer(x);
	}
	setPosition();

	if (inputs.keyboard_F && reg[F])
	{
		TaikoAnimation(F);
		donPressed();
		reg[F] = false;
		timer[F] = 8;
	}
	else if (inputs.keyboard_F == 0)
	{
		reg[F] = true;
	}

	if (inputs.keyboard_D && reg[D])
	{
		TaikoAnimation(D);
		kaPressed();
		reg[D] = false;
		timer[D] = 8;
	}
	else if (inputs.keyboard_D == 0)
	{
		reg[D] = true;
	}

	if (inputs.keyboard_J && reg[J])
	{
		TaikoAnimation(J);
		donPressed();
		reg[J] = false;
		timer[J] = 8;
	}
	else if (inputs.keyboard_J == 0)
	{
		reg[J] = true;
	}

	if (inputs.keyboard_K && reg[K])
	{
		TaikoAnimation(K);
		kaPressed();
		reg[K] = false;
		timer[K] = 8;
	}
	else if (inputs.keyboard_K == 0)
	{
		reg[K] = true;
	}

	checkCombo();
	draw(renderer);
	closemusic(choice);
}

void GameCtrl::setPosition()
{
	double position = speed * currentTime;
	for (int i = len - 1; i >= 0; i--)
	{
		if (color[i] == 3 && beats[i].getX() > 0) {
			beats[i - 1].setX((int)(beats[i - 1].getStartPostion() - position));
			beats[i].setX((int)(beats[i].getStartPostion() - position));
			i--;
		}
		else if (!isBeatFly[i] && beats[i].getX() > 0)
			beats[i].setX((int)(beats[i].getStartPostion() - position));
	}
}

void GameCtrl::TaikoAnimation(int x)
{
	switch (x)
	{
	case F:
		Mix_PlayChannel(-1, donEffect, 0);
		leftdon.setSrcPosition(0, 162 * 3);
		break;
	case D:
		Mix_PlayChannel(-1, kaEffect, 0);
		leftka.setSrcPosition(0, 162);
		break;
	case J:
		Mix_PlayChannel(-1, donEffect, 0);
		rightdon.setSrcPosition(0, 162 * 4);
		break;
	case K:
		Mix_PlayChannel(-1, kaEffect, 0);
		rightka.setSrcPosition(0, 162 * 2);
		break;
	}
}

void GameCtrl::Timer(int x)
{
	if (timer[x] > 0)
		timer[x]--;
	if (timer[x] == 0)
	{
		switch (x)
		{
		case F:
			leftdon.setSrcPosition(0, 0);
			break;
		case D:
			leftka.setSrcPosition(0, 0);
			break;
		case J:
			rightdon.setSrcPosition(0, 0);
			break;
		case K:
			rightka.setSrcPosition(0, 0);
			break;
		default:
			break;
		}
	}
}

void GameCtrl::draw(SDL_Renderer* renderer)
{
	bgPane1a.draw();
	bgPane1b.draw();
	bgPane2.draw();
	bgPane3.draw();
	firework.draw();
	for (int i = 0; i < 30; i++)
		if (backupBeats[i].getX() > 0 && backupBeats[i].getX() < 1920)
			backupBeats[i].draw();
	for (int i = len - 1; i >= 0; i--)
	{
		if (color[i] == 3 && beats[i].getX() > 0 && beats[i - 1].getX() < 1920)
		{
			beats[i - 1].draw();
			i--;
		}
		else if (beats[i].getX() > 0 && beats[i].getX() < 1920)
			beats[i].draw();
	}
	statusPane.draw();
	scorebg.draw();
	Taiko.draw();
	doll.draw();
	leftdon.draw();
	rightdon.draw();
	leftka.draw();
	rightka.draw();
	scoreText.draw();
	comboText.draw();

	if ((combo > redandblue * 2 / 3) || (combo > 30 && combo < 40) || (combo > 60 && combo < 70) || (currentTime >= (beatTime[len - 1] - 7000) && currentTime <= (beatTime[len - 1] - 500))) {
		surprise1.draw();
		surprise2.draw();
		surprise3.draw();
		surprise4.draw();
	}
}

void GameCtrl::createBackGround(SDL_Renderer* renderer)
{
	bgPane1a = Pane(renderer, 0, 0, 1920, 213, "../rsc/image/game_bg_1a.png");
	bgPane1b = Pane(renderer, 0, 0, 1920, 295, "../rsc/image/game_bg_1b.png");
	bgPane1a.setAnimate(0, 0, 2450, 272, LEFT, 2);
	bgPane1b.setAnimate(0, 0, 1886, 295, LEFT, 2);
	bgPane2 = Pane(renderer, 0, 531, 1920, 540, "../rsc/image/game_bg_2a.png");
	bgPane3 = Pane(renderer, 392, 305, 1528, 216, "../rsc/image/game_bg_3.png");
	scorebg = Pane(renderer, 0, 305, 392, 216, "../rsc/image/score_bg1.png");
	statusPane = Pane(renderer, 2000, 1200, 95, 49, 0, 0, 761, 393, "../rsc/image/statusText.png");
	statusPane.UpAndStop(460, 250, 230);

	Taiko = Pane(renderer, 230, 335, 138, 162, 0, 0, 138, 162, "../rsc/image/taiko.png");
	leftdon = Pane(renderer, 230, 335, 138, 162, 0, 0, 138, 162, "../rsc/image/taiko2.png");
	rightdon = Pane(renderer, 230, 335, 138, 162, 0, 0, 138, 162, "../rsc/image/taiko2.png");
	leftka = Pane(renderer, 230, 335, 138, 162, 0, 0, 138, 162, "../rsc/image/taiko2.png");
	rightka = Pane(renderer, 230, 335, 138, 162, 0, 0, 138, 162, "../rsc/image/taiko2.png");

	firework = Sprite(renderer, 361, 255, 270, 270, 20, 5, 4, false, "../rsc/image/beat_explosion.png");
	firework.setFrame(14);
	doll = Sprite(renderer, 60, 120, 348, 179, 38, 10, 4, true, "../rsc/image/don_anim_normal.png");
	surprise1 = Sprite(renderer, 50, 600, 230, 460, 32, 4, 8, true, "../rsc/image/surprise1.png");
	surprise2 = Sprite(renderer, 530, 600, 230, 460, 32, 4, 8, true, "../rsc/image/surprise2.png");
	surprise3 = Sprite(renderer, 1010, 600, 230, 460, 32, 4, 8, true, "../rsc/image/surprise3.png");
	surprise4 = Sprite(renderer, 1490, 600, 230, 460, 32, 4, 8, true, "../rsc/image/surprise4.png");
}

void GameCtrl::setMovingSpeed()
{
	double time = 4.0 * 60.0 * 1000 / bpm;
	speed = 1344.0 / time;
	startPosition = (int)(449 + initTime * speed);
	printf("Speed set\n");
}

void GameCtrl::createBeats(SDL_Renderer* renderer)
{
	beats = new Beat[len];
	for (int i = 0; i < len; i++)
	{
		beats[i] = Beat(renderer, color[i], size[i], index[i], startPosition);
		if (color[i] == 3)
		{
			beats[i] = Beat(renderer, color[i], size[i], index[i], startPosition);
			beats[i].setOrangeLen(index[i + 1] - index[i]);
			i++;
			beats[i] = Beat(renderer, color[i], size[i], index[i], startPosition);
			beats[i].setOrangeLen(0);
		}
	}
	backupBeats = new Beat[30];
	for (int i = 0; i < 30; i++)
	{
		backupBeats[i] = Beat(renderer, 1, false, 100000, startPosition);
	}
	isBeatHit = new bool[len] {false};
	isBeatFly = new bool[len] {false};
	isComboChecked = new bool[len] {false};

	for (int i = 0; i < len; i++)
		if (color[i] == 3)
			isComboChecked[i] = true;
	isPointCount = new bool[len] {false};

}

void GameCtrl::donPressed()
{
	TIME pressTime = currentTime;
	int status = 4;
	int index = findClosest(pressTime);
	if (color[index] == 3 && color[index + 1] == 3 &&
		pressTime >= beatTime[index] && pressTime <= beatTime[index + 1])
	{
		status = 5;
	}
	else if (index != -1)
	{
		status = checkStatus(1, color[index], pressTime, beatTime[index]);
	}
	if (status == 1 || status == 2)
	{
		isBeatHit[index] = true;
		isBeatFly[index] = true;
		if (status == 1)
		{
			statusPane.setSrcPosition(0, 393);
			if (size[index])
				firework.setStartEnd(0, 4, false);
			else
				firework.setStartEnd(10, 14, false);
		}
		else
		{
			statusPane.setSrcPosition(0, 786);
			if (size[index])
				firework.setStartEnd(5, 9, false);
			else
				firework.setStartEnd(15, 19, false);
		}
		statusPane.startTimer(30);
		firework.startTimer(60);
		countPoint(status);
		isPointCount[index] = true;
		combo++;
		// isComboChecked[index] = true;
		beats[index].hitAnimation();
		// setProgressBar(status);
		showPoint();
	}
	else if (status == 3)
	{
		isBeatHit[index] = true;
		statusPane.setSrcPosition(0, 1179);
		statusPane.startTimer(60);
		isComboChecked[index] = true;
		totalBad++;
		// lastcombo += combo;
		combo = 0;
		// setProgressBar(status);
		showPoint();
	}
	else if (status == 5)
	{
		for (int i = 0; i < 30; i++)
		{
			if (backupBeats[i].getAvailable())
			{
				backupBeats[i].setColor(RED);
				backupBeats[i].setSize(size[index]);
				backupBeats[i].hitAnimation();
				break;
			}
		}
		countPoint(status);
		isPointCount[index] = true;
		showPoint();
	}
}

void GameCtrl::kaPressed()
{
	TIME pressTime = currentTime;
	int index = findClosest(pressTime);
	int status = 4;
	if (color[index] == 3 && color[index + 1] == 3 &&
		pressTime >= beatTime[index] && pressTime <= beatTime[index + 1])
	{
		status = 5;
	}
	else if (index != -1)
	{
		status = checkStatus(2, color[index], pressTime, beatTime[index]);
	}

	if (status == 1 || status == 2)
	{
		isBeatHit[index] = true;
		isBeatFly[index] = true;
		if (status == 1)
		{
			statusPane.setSrcPosition(0, 393);
			if (size[index])
				firework.setStartEnd(0, 4, false);
			else
				firework.setStartEnd(10, 14, false);
		}
		else
		{
			statusPane.setSrcPosition(0, 786);
			if (size[index])
				firework.setStartEnd(5, 9, false);
			else
				firework.setStartEnd(15, 19, false);
		}
		statusPane.startTimer(30);
		firework.startTimer(60);
		countPoint(status);
		isPointCount[index] = true;
		combo++;
		// isComboChecked[index] = true;
		beats[index].hitAnimation();
		// setProgressBar(status);
		showPoint();
	}
	else if (status == 3)
	{
		isBeatHit[index] = true;
		statusPane.setSrcPosition(0, 1179);
		statusPane.startTimer(30);
		isComboChecked[index] = true;
		totalBad++;
		combo = 0;
		showPoint();
	}
	else if (status == 5)
	{
		for (int i = 0; i < 30; i++)
		{
			if (backupBeats[i].getAvailable())
			{
				backupBeats[i].setColor(BLUE);
				backupBeats[i].setSize(size[index]);
				backupBeats[i].hitAnimation();
				break;
			}
		}
		countPoint(status);
		isPointCount[index] = true;
		showPoint();
	}
}

void GameCtrl::countPoint(int status)
{

	if (status == 1)
	{
		totalGood++;
		if (combo < 10)
			point += 2060;
		else if (combo < 20)
			point += 2160;
		else if (combo < 30)
			point += 2260;
		else if (combo < 40)
			point += 2360;
		else if (combo < 50)
			point += 2460;
		else if (combo < 60)
			point += 2560;
		else if (combo < 70)
			point += 2660;
		else if (combo < 80)
			point += 2760;
		else if (combo < 90)
			point += 2860;
		else if (combo < 100)
			point += 2960;
	}
	else if (status == 2)
	{
		totalOk++;
		if (combo < 10)
			point += 1030;
		else if (combo < 20)
			point += 1080;
		else if (combo < 30)
			point += 1130;
		else if (combo < 40)
			point += 1180;
		else if (combo < 50)
			point += 1230;
		else if (combo < 60)
			point += 1280;
		else if (combo < 70)
			point += 1330;
		else if (combo < 80)
			point += 1380;
		else if (combo < 90)
			point += 1430;
		else if (combo < 100)
			point += 1480;
	}
	else if (status == 5)
	{
		point += 100;
	}
}

void GameCtrl::showPoint()
{
	if (combo > maxCombo)
		maxCombo = combo;

	char* p = new char[10];
	int temp, i;
	temp = point;
	i = 0;
	while (temp != 0) {
		temp /= 10;
		i++;
	}
	temp = point;
	for (int j = i - 1; j >= 0; j--) {
		p[j] = temp % 10 + '0';
		temp /= 10;

	}

	scoretext = p;

	char* co = new char[10];
	temp = combo;
	i = 0;
	while (temp != 0) {
		temp /= 10;
		i++;
	}
	temp = combo;
	for (int j = i - 1; j >= 0; j--) {
		co[j] = temp % 10 + '0';
		temp /= 10;

	}
	combotext = co;

	scoreText.setString(scoretext);
	scoreText.generateTexture();

	if (combo >= 10 && lastCombo != combo)
	{
		comboText.setString(combotext);
		comboText.generateTexture();
		/*
		for (int o = 0; o < comboScaleTransition.length; o++) {
			if (comboScaleTransition[o].getStatus() == Animation.Status.RUNNING) {
				continue;
			}
			else {
				comboText.setVisible(true);
				comboScaleTransition[o].setNode(comboText);
				comboScaleTransition[o].play();
				break;
			}
		}*/
	}
	else if (combo < 10)
	{
		comboText.setString(" ");
		comboText.generateTexture();
	}
	lastCombo = combo;
}

void GameCtrl::checkCombo()
{
	bool lastPointCount = false;

	for (int i = 0; i < len; i++)
	{
		if (currentTime > beatTime[i] + 90 && !isComboChecked[i] && !isPointCount[i])
		{
			combo = 0;
			// setProgressBar(3);
			showPoint();
			isComboChecked[i] = true;
			break;
		}
	}
}

int GameCtrl::findClosest(TIME pressTime)
{
	int closestIndex = -1;
	int first = 0, last = len - 1, mid;
	TIME shortest = 10000;
	for (int i = 0; i < len - 1; i++)
	{
		if (color[i] == 3 && color[i + 1] == 3 &&
			pressTime > beatTime[i] &&
			pressTime < beatTime[i + 1])
		{
			return i;
		}
	}
	while (first <= last)
	{
		mid = (first + last) / 2;
		if (!isBeatHit[mid] &&
			abs((int)(pressTime - beatTime[mid])) <= 90 &&
			abs((int)(pressTime - beatTime[mid])) <= (int)shortest)
		{
			closestIndex = mid;
			if (shortest == abs((int)(pressTime - beatTime[mid])))
				break;
			else
				shortest = abs((int)(pressTime - beatTime[mid]));
		}
		else if (isBeatHit[mid] &&
			abs((int)(pressTime - beatTime[mid])) <= 90 &&
			abs((int)(pressTime - beatTime[mid])) <= (int)shortest)
		{
			return -1;
		}
		else if ((int)pressTime - (int)beatTime[mid] > 90)
		{
			first = mid + 1;
		}
		else if (beatTime[mid] - pressTime > 90)
		{
			last = mid - 1;
		}
	}
	return closestIndex;
}

int GameCtrl::checkStatus(int color, int checkColor, TIME pressTime, TIME checkTime)
{
	int goodDomain = 50, okDomain = 75, badDomain = 90;

	if (checkColor == color)
	{
		if (abs((int)(pressTime - checkTime)) < goodDomain)
			return 1;
		else if (abs((int)(pressTime - checkTime)) < okDomain)
			return 2;
		else if (abs((int)(pressTime - checkTime)) < badDomain)
			return 3;
		else
			return 4;
	}
	else if (checkColor == 3)
	{
		if (abs((int)(pressTime - checkTime)) < goodDomain)
			return 5;
		else
			return 4;
	}
	else
	{
		return 4;
	}
}

void GameCtrl::loadAudio(int songnumber)
{
	music = Mix_LoadMUS(songPath);
	if (music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}

	donEffect = Mix_LoadWAV("../rsc/audio/don.wav");
	if (donEffect == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}

	kaEffect = Mix_LoadWAV("../rsc/audio/ka.wav");
	if (kaEffect == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}
	scoremusic = Mix_LoadMUS("../rsc/audio/score.wav");
	if (scoremusic == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}
}

void GameCtrl::setText(SDL_Renderer* renderer)
{
	//fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
	scoretext = "0";
	combotext = " ";

	Uint16 good[] = { 0x826F };
	Uint16 ok[] = { 0x53EF };
	Uint16 bad[] = { 0x4E0D, 0x53EF };
	SDL_Color goodGradient[2] = { {255, 255, 0}, {255, 90, 0} };
	SDL_Color basGradient[3] = { {61, 129, 255}, {95, 61, 255}, {0, 236, 255} };
	const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
	scoreText = Text(scoretext, fontPath, 40, { 255, 255, 255 }, renderer, { 20, 320 });
	comboText = Text(combotext, fontPath, 45, { 0, 0, 0 }, renderer, { 272, 372 });

	printf("Text set\n");
}

void GameCtrl::modify(int& x, int& y)
{
	double mx, my;
	RenderWindow::getmodify(mx, my);

	x = (int)(x * mx);
	y = (int)(y * my);
}

void GameCtrl::demodify(int& x, int& y)
{
	double mx, my;
	RenderWindow::getmodify(mx, my);

	x = (int)(x / mx);
	y = (int)(y / my);
}

int GameCtrl::closemusic(int songname)
{
	// stop music and change game scene to score scene
	if (currentTime >= (beatTime[len - 1] + 4000))
	{
		// if (lastcombo != combo) {
		// lastcombo += combo;
		//}
		// printf("point = %d, combo = %d, good = %d, ok = %d, bad = %d\n", point, combo, totalGood, totalOk, totalBad);
		if (Mix_PlayingMusic() == 1)
		{
			Mix_PauseMusic();
			Mix_PlayMusic(scoremusic, 0);
		}

		Mix_Quit();
		return 3;
	}
	return 2;
}

int GameCtrl::getpoint()
{
	return point;
}
int GameCtrl::getgood()
{
	return totalGood;
}
int GameCtrl::getok()
{
	return totalOk;
}
int GameCtrl::getbad()
{
	return totalBad;
}

int GameCtrl::getcombo()
{
	return maxCombo;
}
int GameCtrl::getlastcombo()
{
	return lastCombo;
}

int GameCtrl::getSong()
{
	return choice;
}