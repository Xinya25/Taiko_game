#pragma once
#include <time.h>
#include <SDL.h>

class SongData
{
private:
    int songNum;

protected:
    static int choice;
    static int len; // array length(beats number)
    static int bpm;
    static char* songName;
    static Uint32 initTime;
    static char* songPath;
    static char** folderPath;
    static char** folderName;
    static int* color;
    static int* index;
    static bool* size;
    static Uint32* beatTime;
    static int redandblue;

public:
    SongData();
    void  directory();
    void readFile();
    int getSongNum();
    //void Write();
    void close();
};
