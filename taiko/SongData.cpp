#include "SongData.h"
#include <tchar.h> 
#include <string>
#include <iostream>
#include "SDL_mixer.h"
using namespace std;

int     SongData::choice = 0;
int     SongData::len = 0;
int     SongData::bpm = 0;
char* SongData::songName;
Uint32  SongData::initTime = 0;
char** SongData::folderPath;
char** SongData::folderName;
char* SongData::songPath;
int* SongData::color;
int* SongData::index;
bool* SongData::size;
Uint32* SongData::beatTime;
int SongData::redandblue = 0;


SongData::SongData()
{
}


/*void SongData::Write() {
    SongData student;
    FILE* fp;
    if ((fopen_s(&fp, "../data/song0/data.dat", "wb")) != 0)
    {
        printf("Cannot open file.\n");
        exit(1);
    }

    fwrite(&student, sizeof(student), 1, fp);
    fclose(fp);
    printf("\nFile of struct created.\n");
}
*/


#include <windows.h>
void SongData::directory()
{
    // folder pinter
    WIN32_FIND_DATA ffd;
    // folder path
    TCHAR szDir[MAX_PATH] = TEXT("..\\data\\*");
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

    songNum = 0;
    do
    {
        // count how many folders
        if (_tcscmp(ffd.cFileName, parent) && _tcscmp(ffd.cFileName, child)
            && ffd.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
        {
            songNum++;
        }

    } while (FindNextFile(hFind, &ffd) != 0);

    folderPath = new char* [songNum];
    folderName = new char* [songNum];

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        cout << "Folder \"data\" is gone\n";
    }

    int i = 0;
    do
    {
        // if not parent or child, copy folder name to memory
        if (_tcscmp(ffd.cFileName, parent) && _tcscmp(ffd.cFileName, child)
            && ffd.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
        {
            folderPath[i] = new char[200];
            folderName[i] = new char[80];
            sprintf_s(folderPath[i], 200, "..\\data\\%ws", ffd.cFileName);
            sprintf_s(folderName[i], 80, "%ws", ffd.cFileName);
            i++;
        }
    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

}

void SongData::readFile()
{
    redandblue = 0;
    char* dataPath = new char[50];
    strcpy_s(dataPath, 50, folderPath[choice]);
    strcat_s(dataPath, 50, "\\data.txt");

    songPath = new char[50];
    strcpy_s(songPath, 50, folderPath[choice]);
    strcat_s(songPath, 50, "\\song.wav");

    FILE* f_in;

    char line[100];
    if (fopen_s(&f_in, dataPath, "r"))
    {
        printf("Failed to open file.\n");
    }

    int count = 0;

    while (fgets(line, 100, f_in) != NULL)
    {
        if (!strcmp(line, "BPM :\n"))
        {
            fscanf_s(f_in, "%d", &bpm);
        }
        else if (!strcmp(line, "Track name :\n"))
        {
            songName = new char[100];
            fscanf_s(f_in, " ");
            fgets(songName, 100, f_in);
            songName[strlen(songName) - 1] = '\0';
        }
        else if (!strcmp(line, "Start Duration :\n"))
        {
            fscanf_s(f_in, "%d", &initTime);
        }
        else if (!strcmp(line, "array length :\n"))
        {
            fscanf_s(f_in, "%d", &len);
            color = new int[len];
            index = new int[len];
            size = new bool[len];
            beatTime = new Uint32[len];
        }
        else if (!strcmp(line, "Beat no.\n"))
        {
            fscanf_s(f_in, "%d", &index[count]);

            fscanf_s(f_in, " ");
            fgets(line, 100, f_in);

            fscanf_s(f_in, "%d", &(color[count]));
            if (color[count] == 1 || color[count] == 2) {
                redandblue++;
            }

            fscanf_s(f_in, " ");
            fgets(line, 100, f_in);

            char temp[7];
            fscanf_s(f_in, " ");
            fgets(temp, 100, f_in);
            if (!strcmp(temp, "false\n"))
            {
                size[count] = false;
            }
            else
            {
                size[count] = true;
            }

            fscanf_s(f_in, " ");
            fgets(line, 100, f_in);

            double d;
            fscanf_s(f_in, "%lf", &d);
            beatTime[count] = (int)d;

            count++;
        }

        fscanf_s(f_in, " ");
    }

    fclose(f_in);
    cout << "total red and blue = " << redandblue << endl;
}

int SongData::getSongNum()
{
    return songNum;
}

void SongData::close()
{
    Mix_PauseMusic();
    Mix_Quit();
}