#include "ScoreCtrl.h"
#include <iostream>
//#include <tchar.h> 
#include <string.h>
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "GameCtrl.h"

using namespace std;
ScoreCtrl::ScoreCtrl() : GameCtrl()
{
}
ScoreCtrl::ScoreCtrl(SDL_Renderer* renderer, GameCtrl p)
{
    bg = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/score_bg.png");

    point = p.getpoint();
    totalGood = p.getgood();
    totalBad = p.getbad();
    totalOk = p.getok();
    combo = p.getcombo();
    lastCombo = p.getlastcombo();
    //printf("bad %d, last combo %d\n", p.getbad(), p.getlastcombo());

    //cout << "total red and blue = " << redandblue << endl;
    fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
    //songnametext = "song name: ";
    char* str = new char[100];
    strcpy_s(str, 50, "song name: ");
    strcat_s(str, 50, folderName[choice]);
    songnametext = str;

    scoretext = "score: ";
    int i = 250;

    // mostcombo, combo, and define button

    changIntToConst();

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


    nameText = Text(songnametext, fontPath, 40, { 0, 0, 0 }, renderer, { 800, 120 });

    Combo = Pane(renderer, 1400, 250, 160, 80, "../rsc/image/combo.png");
    mostcombo = Pane(renderer, 1400, 350, 220, 80, "../rsc/image/most_combo.png");
    scoreText = Text(scoretext, fontPath, 35, { 0, 0, 0 }, renderer, { 900, 550 });

    statusgood = Pane(renderer, 900, 250, 100, 80, "../rsc/image/statusgood.png");
    statusok = Pane(renderer, 900, 350, 100, 80, "../rsc/image/statusok.png");
    statusbad = Pane(renderer, 900, 450, 120, 70, "../rsc/image/statusbad.png");

    exitBtn = Button(renderer, 50, 50, 100, 100);
    exitBtn.setStroke(10, 0, 0, 0);
    exitBtn.setCorner(10);

    player = Text("Record?", fontPath, 45, { 255, 255, 255 }, renderer, { 250, 120 });
    log = Text("Enter name:", fontPath, 45, { 0, 0, 0 }, renderer, { 240, 120 });
    playerchoose = Button(renderer, 200, 100, 400, 100);
    playerchoose.setStroke(10, 0, 0, 0);

    playername = Button(renderer, 200, 400, 500, 100);
    playername.setStroke(10, 0, 0, 0);


    rank = Button(renderer, 100, 800, 300, 100, "Rank", 40, { 50, 50, 50 });
    rank.setStroke(10, 0, 0, 0);
    flag = false;

    //Textinput
    name = Text(" ", fontPath, 45, { 0, 0, 0 }, renderer, { 240, 420 });
    tin = TextInput(name);
    name.close();

    //button => record data;
    record = Button(renderer, 200, 600, 150, 100);
    record.setStroke(10, 0, 0, 0);
    re = 0; last_point = 0;
    int sum = redandblue;
    if (totalGood == sum) {
        people = true;
        crown = Pane(renderer, 750, 300, 74, 96, 0, 144, 37, 48, "../rsc/image/grade_level.png");
        flower = Pane(renderer, 0, 920, 1932, 159, 0, 318, 1932, 159, "../rsc/image/score_bg_flower.png");
        people_all = Pane(renderer, 775, 630, 553, 416, 0, 0, 553, 416, "../rsc/image/score_bg_animation1.png");
        people_m = Pane(renderer, 500, 655, 292, 425, 0, 425, 292, 425, "../rsc/image/score_bg_animation2.png");
        people_f = Pane(renderer, 1330, 655, 292, 425, 292, 425, 292, 425, "../rsc/image/score_bg_animation2.png");
    }
    else if (totalGood + totalOk == sum) {
        people = true;
        crown = Pane(renderer, 750, 300, 74, 96, 0, 96, 37, 48, "../rsc/image/grade_level.png");
        flower = Pane(renderer, 0, 920, 1932, 159, 0, 318, 1932, 159, "../rsc/image/score_bg_flower.png");
        people_all = Pane(renderer, 775, 630, 553, 416, 0, 0, 553, 416, "../rsc/image/score_bg_animation1.png");
        people_m = Pane(renderer, 500, 655, 292, 425, 0, 425, 292, 425, "../rsc/image/score_bg_animation2.png");
        people_f = Pane(renderer, 1330, 655, 292, 425, 292, 425, 292, 425, "../rsc/image/score_bg_animation2.png");
    }
    else if (totalGood + totalOk > sum * 2 / 3) {
        people = true;
        crown = Pane(renderer, 750, 300, 74, 96, 0, 48, 37, 48, "../rsc/image/grade_level.png");
        flower = Pane(renderer, 0, 920, 1932, 159, 0, 159, 1932, 159, "../rsc/image/score_bg_flower.png");
        people_all = Pane(renderer, 775, 630, 553, 416, 0, 0, 553, 416, "../rsc/image/score_bg_animation1.png");
        people_m = Pane(renderer, 500, 655, 292, 425, 0, 0, 292, 425, "../rsc/image/score_bg_animation2.png");
        people_f = Pane(renderer, 1330, 655, 292, 425, 292, 0, 292, 425, "../rsc/image/score_bg_animation2.png");
    }
    else {
        people = false;
        crown = Pane(renderer, 750, 300, 74, 96, 0, 0, 37, 48, "../rsc/image/grade_level.png");
        flower = Pane(renderer, 0, 920, 1932, 159, 0, 0, 1932, 159, "../rsc/image/score_bg_flower.png");
        /*noshow*/people_all = Pane(renderer, 775, 630, 0, 0, 0, 0, 553, 416, "../rsc/image/score_bg_animation1.png");
        people_m = Pane(renderer, 500, 655, 292, 425, 0, 850, 292, 425, "../rsc/image/score_bg_animation2.png");
        people_f = Pane(renderer, 1330, 655, 292, 425, 292, 850, 292, 425, "../rsc/image/score_bg_animation2.png");
    }

}

void ScoreCtrl::control(SDL_Renderer* renderer, Input& inputs, int& scene)
{
    if (people) {
        people_m.people_move(100);
        people_f.people_move(100);
        people_all.people_move(120);
        people = false;
    }

    if (inputs.keyboard_Esc || exitBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
    {
        inputs.mouse_Left = 0;
        Mix_PauseMusic();
        flag = false; re = false;
        scene = 1;
    }

    if (playerchoose.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y)) {
        flag = ~flag;
    }
    if (flag) {
        tin.setPos({ 240, 420 });
        tin.edit(inputs);

        // if finish name, record the score to .txt file 
        if (!re && record.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y)) {

            playerName = tin.getString();
            //cout << "Textinput = " << playerName << endl;
            writeFile();
            re = ~re;
            //flag = ~flag;
        }
    }
    if (rank.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y)) {
        char* ss = new char[5];
        strcpy_s(ss, 5, " \0");
        tin.setText(ss);
        scene = 6;

    }

}

void ScoreCtrl::readOldFile()
{

    FILE* f_in, * f_copy;
    // the file that copy last score
    fopen_s(&f_in, "../playerData/copy.dat", "wb");
    if (!f_in)
    {
        printf("Cannot open file.\n");
        exit(1);
    }

    // player name you tape 
    playerName = tin.getString();
    /*
    create a dynamic char array to store the player's name and
    cut off space at the first char
    combine the file location and file name in the char s[30]
    open file.
    */
    char* Name = new char[40];
    strcpy_s(Name, 40, playerName);
    // cout <<  Name << endl;
    int i, temp = (int)strlen(playerName);
    for (i = 0; i < temp - 1; i++) {
        Name[i] = playerName[i + 1];
    }
    Name[i] = '\0';
    //char s[30] = "../playerData/";
    strcpy_s(s, "\0");
    strcat_s(s, "../playerData/");
    strcat_s(s, 40, folderName[choice]);
    strcat_s(s, "/");
    strcat_s(s, 40, Name);
    strcat_s(s, 40, ".txt");
    //cout << s << endl;
    int f = 1;

    fopen_s(&f_copy, s, "r");
    if (!f_copy) {
        printf("read copy file Cannot open file!\n");
        f = false;
        // exit(2);
    }

    char line[30];
    int d;
    if (f) {
        while (fgets(line, 30, f_copy)) {
            if (!strcmp(line, "Song name: \n")) {
                fscanf_s(f_copy, "%d", &d);
                fwrite(&d, sizeof(d), 1, f_in);
            }
            else if (!strcmp(line, "score: \n")) {
                fscanf_s(f_copy, "%d", &d);
                fwrite(&d, sizeof(d), 1, f_in);
            }
        }
        f = 0;
        printf("\ncreate copy of file\n");
        fclose(f_copy);
    }

    fclose(f_in);
}

void ScoreCtrl::writeFile()
{
    readOldFile();

    // open copy file
    FILE* f_in;
    fopen_s(&f_in, "../playerData/copy.dat", "rb");
    if (!f_in) {
        printf("Cannot open read copy file.\n");
        exit(1);
    }

    // find which song and last score
    last_song = 0, last_point = 0;
    /*
    while (fgets(line, 30, f_in)) {
        if (!strcmp(line, "Song name: \n")) {
            fscanf_s(f_in, "%d", &last_song);
            //cout << "song = " << last_song << endl;
        }
        else if (!strcmp(line, "score: \n")) {
            fscanf_s(f_in, "%d", &last_point);
            cout << "last point = " << last_point << endl;
        }
    }*/
    rewind(f_in);
    fread(&last_song, sizeof(last_song), 1, f_in);
    fread(&last_point, sizeof(last_point), 1, f_in);

    fclose(f_in);

    cout << "last = " << last_point << endl;
    if (last_point <= point) {
        FILE* f_out;
        fopen_s(&f_out, s, "w");
        if (!f_out) {
            cerr << "write file Cannot open file \n";
            exit(5);
        }
        fprintf(f_out, "Song name: \n%d\n", GameCtrl::getSong());
        fprintf(f_out, "score: \n%d\n", point);
        fprintf(f_out, "Good: \n%d\n", totalGood);
        fprintf(f_out, "Ok: \n%d\n", totalOk);
        fprintf(f_out, "Bad: \n%d\n", totalBad);
        fprintf(f_out, "Combo: \n%d\n", combo);
        fprintf(f_out, "Last Combo: \n%d\n", lastCombo);
        fclose(f_out);
        cout << "\nupdate new score\n";
    }
    else
        cout << "\nlast score is better\n";
}


void ScoreCtrl::draw(SDL_Renderer* renderer)
{
    bg.draw();
    int x1 = 740, y1 = 100, x2 = 1800, y2 = 610, rad = 20, no = 0;
    bg.modify(x1, y1);
    bg.modify(x2, y2);
    bg.modify(rad, no);
    roundedBoxColor(renderer, x1, y1, x2, y2, rad, 0xFFFFFFFF);
    exitBtn.draw(255, 165, 0);
    nameText.draw();
    scoreText.draw();
    goodText.draw();
    okText.draw();
    badText.draw();
    statusgood.draw();
    statusok.draw();
    statusbad.draw();
    Combo.draw();
    mostcombo.draw();
    comboText.draw();
    pointText.draw();
    mostcomboText.draw();
    crown.draw();
    flower.draw();
    people_all.draw();
    people_m.draw();
    people_f.draw();
    rank.draw(200, 250, 250);

    if (flag) {
        playerchoose.draw(255, 255, 255);
        log.draw();
        playername.draw(255, 255, 255);
        if (!re)
            record.draw(255, 0, 255);
        else
            record.draw(255, 255, 100);
        tin.draw();
    }
    else {
        playerchoose.draw(255, 165, 0);
        player.draw();
    }
}

void ScoreCtrl::changIntToConst()
{
    /*
        point = p.getpoint();
    totalGood = p.getgood();
    totalBad = p.getbad();
    totalOk = p.getok();
    combo = p.getcombo();
    lastCombo = p.getlastcombo();
    */
    int i = 0;
    char* good = new char[10];
    char* ok = new char[10];
    char* bad = new char[10];
    char* co = new char[10];
    char* lco = new char[10];
    char* p = new char[10];
    int temp;

    // totalGood int to const char*
    temp = totalGood;
    i = 0;
    while (temp != 0) {
        temp /= 10;
        i++;
    }
    temp = totalGood;
    for (int j = i - 1; j >= 0; j--) {
        good[j] = temp % 10 + '0';
        temp /= 10;
    }
    totalgoodtext = good;

    // point  int to const char*
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
    score = p;

    // totalOk int to const char*
    temp = totalOk;
    i = 0;
    while (temp != 0) {
        temp /= 10;
        i++;
    }
    temp = totalOk;
    for (int j = i - 1; j >= 0; j--) {
        ok[j] = temp % 10 + '0';
        temp /= 10;

    }
    totaloktext = ok;


    //totalBad int to const char*
    temp = totalBad;
    i = 0;
    while (temp != 0) {
        temp /= 10;
        i++;
    }
    temp = totalBad;
    for (int j = i - 1; j >= 0; j--) {
        bad[j] = temp % 10 + '0';
        temp /= 10;

    }
    totalbadtext = bad;


    //combo int to const char*
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

    //lastcombo int to const char*
    temp = lastCombo;
    i = 0;
    while (temp != 0) {
        temp /= 10;
        i++;
    }
    temp = lastCombo;
    for (int j = i - 1; j >= 0; j--) {
        lco[j] = temp % 10 + '0';
        temp /= 10;

    }
    lastcombotext = lco;

}

void ScoreCtrl::close()
{
    delete[] totalbadtext;
    delete[] totalgoodtext;
    delete[] totaloktext;
    delete[] combotext;
    delete[] lastcombotext;
    delete[] score;
    delete[] songnametext;
    delete[] playerName;

}