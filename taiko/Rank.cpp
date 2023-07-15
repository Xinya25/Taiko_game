#include <iostream>
#include <tchar.h> 
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <atlstr.h>
#include "Rank.h"
using namespace std;

Rank::Rank() :ScoreCtrl()
{
}
Rank::Rank(SDL_Renderer* renderer)
{
    pushbutton = false;
    fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";

    bg = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/page1_bg.png");
    scoretext = "score: ";
    Combo = Pane(renderer, 1400, 250, 160, 80, "../rsc/image/combo.png");
    mostcombo = Pane(renderer, 1400, 350, 220, 80, "../rsc/image/most_combo.png");
    //scoreText = Text(scoretext, fontPath, 35, { 0, 0, 0 }, renderer, { 900, 550 });

    statusgood = Pane(renderer, 900, 250, 100, 80, "../rsc/image/statusgood.png");
    statusok = Pane(renderer, 900, 350, 100, 80, "../rsc/image/statusok.png");
    statusbad = Pane(renderer, 900, 450, 120, 70, "../rsc/image/statusbad.png");

    exitBtn = Button(renderer, 50, 50, 100, 100);
    exitBtn.setStroke(10, 0, 0, 0);
    exitBtn.setCorner(10);
    title = Text("Rank", fontPath, 80, { 0, 0, 0 }, renderer, { 270, 130 });
    playerRank();
    RankScore(renderer);

}

void Rank::playerRank()
{

    // folder pinter
    WIN32_FIND_DATA ffd;
    // folder path 
    char* str = new char[100];
    strcpy_s(str, 50, "..\\playerData\\");
    strcat_s(str, 50, folderName[choice]);
    strcat_s(str, 50, "\\*");
    //cout << str << endl;
    //TCHAR szDir[MAX_PATH] = TEXT("..\\playerData\\GEAR_UP\\*.*");
    TCHAR szDir[MAX_PATH];
    _tcscpy_s(szDir, CA2W(str));

    // find folder 
    HANDLE hFind = INVALID_HANDLE_VALUE;

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        // pirint folder is broken
        cout << "Folder \"data\" is gone\n";
    }

    // to upper level folder
    TCHAR parent[] = _T("..");
    // this level folder
    TCHAR child[] = _T(".");

    txtNum = 0;
    do
    {
        // count how many folders
        if (_tcscmp(ffd.cFileName, parent) && _tcscmp(ffd.cFileName, child)
            && ffd.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
        {
            txtNum++;
        }

    } while (FindNextFile(hFind, &ffd) != 0);

    playerPath = new char* [txtNum];
    playerName = new char* [txtNum];

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        cout << "Folder \"playerData\" is gone\n";
    }

    int i = 0;
    do
    {
        // if not parent or child, copy folder name to memory
        if (_tcscmp(ffd.cFileName, parent) && _tcscmp(ffd.cFileName, child)
            && ffd.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
        {
            playerPath[i] = new char[200];
            playerName[i] = new char[80];
            sprintf_s(playerPath[i], 200, "..\\playerData\\%s\\%ws", folderName[choice], ffd.cFileName);
            sprintf_s(playerName[i], 80, "%ws", ffd.cFileName);
            //cout << playerPath[i] << endl;
            cout << playerName[i] << " " << sizeof(playerName[i]) << endl;
            i++;
        }
    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);


}

void Rank::control(SDL_Renderer* renderer, Input& inputs, int& scene)
{
    if (inputs.keyboard_Esc || exitBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
    {
        scene = 3;
        Mix_PauseMusic();
    }
    for (int i = 0; i < txtNum; i++)
    {
        if (txtName[i].getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
        {
            Readtxt(renderer, i);
            pushbutton = ~pushbutton;

        }
    }
}
void Rank::RankScore(SDL_Renderer* renderer)
{
    FILE* f;
    char line[100];
    scorerank = new int* [txtNum];
    playerScore = new int[txtNum];
    for (int i = 0; i < txtNum; i++)
        scorerank[i] = new int[2];

    for (int i = 0; i < txtNum; i++) {
        scorerank[i][0] = i;
        fopen_s(&f, playerPath[i], "r");
        if (f == NULL)
        {
            printf("Failed to open rank file.\n");
        }
        while (fgets(line, 100, f) != NULL)
        {
            if (!strcmp(line, "score: \n"))
            {
                fscanf_s(f, "%d", &playerScore[i]);
            }
        }
        fclose(f);
        scorerank[i][1] = playerScore[i];
        //cout << scorerank[i][1] << endl;

    }
    /*
    for (int i = 0; i < txtNum; i++) {
        for (int j = 0; j < 2; j++) {
            cout << scorerank[i][j] << " ";

        }
        cout << endl;
    }*/


    for (int i = 0; i < txtNum - 1; i++) {
        for (int j = i + 1; j < txtNum; j++) {
            // if the txtfile's score is poor than the lower txt file in the folder,
            // then change the rank
            if (scorerank[i][1] < scorerank[j][1]) {
                int temp = scorerank[i][1];
                int t = scorerank[i][0];
                scorerank[i][1] = scorerank[j][1];
                scorerank[j][1] = temp;
                scorerank[i][0] = scorerank[j][0];
                scorerank[j][0] = t;

            }
        }
    }/*
    for (int i = 0; i < txtNum; i++) {
        for (int j = 0; j < 2; j++) {
            cout << scorerank[i][j] << " ";

        }
        cout << endl;
    }*/
    txtName = new Button[txtNum];
    ranking = new Text[txtNum];
    for (int i = 0; i < txtNum; i++) {
        for (int j = 0; j < txtNum; j++) {
            if (j == scorerank[i][0]) {
                char c = i + '0' + 1;
                char* r = new char[5];
                r[0] = c;
                ranking[i] = Text(r, fontPath, 45, { 0, 0, 0 }, renderer, { 180, 255 + 120 * i });
                txtName[i] = Button(renderer, 250, 250 + 120 * i, 400, 80, playerName[j], 40, { 50, 50, 50 });
                txtName[i].setStroke(10, 0, 0, 0);
            }
        }

    }


}

void Rank::Readtxt(SDL_Renderer* renderer, int r)
{
    FILE* f;
    int x = scorerank[r][0];
    char line[100];
    fopen_s(&f, playerPath[x], "r");
    if (f == NULL)
    {
        printf("Failed to open rank file.\n");
    }
    while (fgets(line, 100, f) != NULL)
    {
        if (!strcmp(line, "score: \n"))
        {
            fscanf_s(f, "%d", &point);
        }
        else if (!strcmp(line, "Good: \n")) {
            fscanf_s(f, "%d", &totalGood);
        }
        else if (!strcmp(line, "Ok: \n")) {
            fscanf_s(f, "%d", &totalOk);
        }
        else if (!strcmp(line, "Bad: \n")) {
            fscanf_s(f, "%d", &totalBad);
        }
        else if (!strcmp(line, "Combo: \n")) {
            fscanf_s(f, "%d", &combo);
        }
        else if (!strcmp(line, "Last Combo: \n")) {
            fscanf_s(f, "%d", &lastCombo);
        }

    }
    fclose(f);
    ScoreCtrl::changIntToConst();
    int i = 250;
    pointText = Text(score, fontPath, 35, { 0, 0, 0 }, renderer, { 1400 - i, 550 });
    goodText = Text(totalgoodtext, fontPath, 35, { 0, 0, 0 }, renderer, { 1400 - i, 260 });
    if (totalOk == 0)
        okText = Text("0", fontPath, 35, { 0, 0, 0 }, renderer, { 1400 - i, 370 });
    else
        okText = Text(totaloktext, fontPath, 35, { 0, 0, 0 }, renderer, { 1400 - i, 370 });
    if (totalBad == 0)
        badText = Text("0", fontPath, 35, { 0, 0, 0 }, renderer, { 1400 - i, 470 });
    else
        badText = Text(totalbadtext, fontPath, 35, { 0, 0, 0 }, renderer, { 1400 - i, 470 });

    comboText = Text(combotext, fontPath, 35, { 0, 0, 0 }, renderer, { 1700, 260 });
    if (lastCombo == 0)
        mostcomboText = Text("0", fontPath, 35, { 0, 0, 0 }, renderer, { 1700, 380 });
    else
        mostcomboText = Text(lastcombotext, fontPath, 35, { 0, 0, 0 }, renderer, { 1700, 380 });
    scoreText = Text("score: ", fontPath, 35, { 0, 0, 0 }, renderer, { 900, 550 });
    nameText = Text(folderName[choice], fontPath, 40, { 0, 0, 0 }, renderer, { 900, 120 });

}

void Rank::draw(SDL_Renderer* renderer)
{
    bg.draw();
    if (pushbutton) {
        int x1 = 800, y1 = 100, x2 = 1780, y2 = 610, rad = 20, no = 0;
        bg.modify(x1, y1);
        bg.modify(x2, y2);
        bg.modify(rad, no);
        roundedBoxColor(renderer, x1, y1, x2, y2, rad, 0xFFFFFFFF);
        statusgood.draw();
        statusok.draw();
        statusbad.draw();
        Combo.draw();
        mostcombo.draw();
        goodText.draw();
        okText.draw();
        badText.draw();
        comboText.draw();
        pointText.draw();
        mostcomboText.draw();
        scoreText.draw();
        nameText.draw();
    }

    exitBtn.draw(255, 160, 0);

    title.draw();
    //scoreText.draw();
    /*
    goodText.draw();
    okText.draw();
    badText.draw();
    comboText.draw();
    pointText.draw();
    mostcomboText.draw();*/
    for (int i = 0; i < txtNum; i++) {
        txtName[i].draw(230, 230, 200);
        ranking[i].draw();
    }
}

