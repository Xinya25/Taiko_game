#include "SceneManager.h"


SceneManager::SceneManager()
{
}

SceneManager::SceneManager(SDL_Renderer* renderer)
{
    init = false;
    init3 = false;
    init4 = false;
    init6 = false;
    cursor = Pane(renderer, 0, 0, 50, 50, "../rsc/image/cursor.png");
    keyboard = SDL_GetKeyboardState(NULL);
    SDL_ShowCursor(SDL_DISABLE);
    hctrl = HomeCtrl(renderer);
    mctrl = MenuCtrl(renderer);
    stctrl = StartCtrl(renderer);
}

void SceneManager::manage(SDL_Renderer* renderer, bool& quit)
{
    getEvent(renderer, quit);

    switch (scene)
    {
    case 0:
        hctrl.control(renderer, input, scene, quit);
        hctrl.draw(renderer);
        break;
    case 1:
        if (!init1)
        {
            mctrl = MenuCtrl(renderer);
            init1 = true;
        }
        mctrl.control(renderer, input, scene);
        mctrl.draw(renderer);
        break;
    case 2:
        if (!init)
        {
            SongData data;

            gctrl = GameCtrl(renderer);

            init = true;
            init3 = false;
            init6 = false;
        }
        gctrl.control(renderer, input, scene);
        scene = gctrl.closemusic(0);
        if (input.keyboard_Esc)
        {
            scene = 1;
            gctrl.close();
            init = false;
        }

        break;
        // scene = 3, to socre page
    case 3:
        if (!init3)
        {
            sctrl = ScoreCtrl(renderer, gctrl);
            init3 = true;
        }
        sctrl.control(renderer, input, scene);
        sctrl.draw(renderer);
        init = false;

        break;

        // scene = 4; to produce music
    case 4:
        if (!init4)
        {
            producer = Producer(renderer);
            init4 = true;
            init1 = false;
        }
        producer.control(input, scene);
        producer.draw(renderer);
        break;
    case 6:
        if (!init6) {
            rank = Rank(renderer);
            init6 = true;
        }
        rank.control(renderer, input, scene);
        rank.draw(renderer);
        break;
    case 10:
        stctrl.control(renderer, input, scene, quit);
        stctrl.draw(renderer);
        break;
    }

    if (input.keyboard_Esc)
    {
        scene = 0;
        //gctrl.close();
        init = false;
    }

    if (scene != 5)
    {
        input.mouse_Left = 0;
        input.mouse_Right = 0;
    }

    cursor.getDst()->x = input.mouse_X - cursor.getWidth() / 2;
    cursor.getDst()->y = input.mouse_Y - cursor.getHeight() / 2;
    cursor.draw();
}

void SceneManager::getEvent(SDL_Renderer* renderer, bool& quit)
{
    SDL_PumpEvents();
    SDL_GetMouseState(&input.mouse_X, &input.mouse_Y);

    input.isEvent = false;
    while (SDL_PollEvent(&event))
    {
        input.isEvent = true;
        input.type = event.type;
        switch (input.type)
        {
        case SDL_QUIT:
            quit = true;

        case SDL_MOUSEBUTTONUP:
            //input.type = SDL_MOUSEBUTTONUP;
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                input.mouse_Left = 1;
                break;
            case SDL_BUTTON_RIGHT:
                input.mouse_Right = 1;
                break;
            }
            break;

        case SDL_KEYDOWN:
            if (event.key.repeat == 0)
            {
                // Detect UI hotkeys
                input.keyboard_Esc = keyboard[SDL_SCANCODE_ESCAPE];
                input.keyboard_F = keyboard[SDL_SCANCODE_F];
                input.keyboard_D = keyboard[SDL_SCANCODE_D];
                input.keyboard_J = keyboard[SDL_SCANCODE_J];
                input.keyboard_K = keyboard[SDL_SCANCODE_K];
                input.keyboard_LEFT = keyboard[SDL_SCANCODE_LEFT];
                input.keyboard_RIGHT = keyboard[SDL_SCANCODE_RIGHT];

                input.keySym = event.key.keysym.sym;
            }
            break;

        case SDL_KEYUP:
            if (event.key.repeat == 0)
            {
                // Detect UI hotkeys
                input.keyboard_Esc = keyboard[SDL_SCANCODE_ESCAPE];
                input.keyboard_F = keyboard[SDL_SCANCODE_F];
                input.keyboard_D = keyboard[SDL_SCANCODE_D];
                input.keyboard_J = keyboard[SDL_SCANCODE_J];
                input.keyboard_K = keyboard[SDL_SCANCODE_K];
                input.keyboard_LEFT = keyboard[SDL_SCANCODE_LEFT];
                input.keyboard_RIGHT = keyboard[SDL_SCANCODE_RIGHT];

                input.keySym = event.key.keysym.sym;
            }
            break;

        case SDL_MOUSEWHEEL:
            input.mouse_Wheel = event.wheel.y;
            break;

        case SDL_TEXTINPUT:
            strcpy_s(input.keyTyped, 32, event.text.text);
            break;

        case SDL_DROPFILE:
            strcpy_s(input.dropfiledir, 200, event.drop.file);
            break;
        }
    }
}
