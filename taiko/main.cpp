#include "SceneManager.h"
#include "RenderWindow.h"
#include "System.h"
#include "Const.h"
#include <stdio.h>

int main(int argc, char* args[])
{
    System sdl;
    sdl.init();

    RenderWindow window("Project", 0, 0, 80);
    // name, winx, winy, percentage of full screen

    SceneManager manager(window.getRenderer());

    bool quit = false;
    while (!quit)
    {
        window.clear();
        manager.manage(window.getRenderer(), quit);
        window.display();
    }

    window.close();
    sdl.close();
    return 0;
}