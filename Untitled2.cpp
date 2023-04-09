
#include "commonfunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init( SDL_INIT_VIDEO);
    if(ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //Create window
    g_window = SDL_CreateWindow("SDL 2.0 Game bai tap lon",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(g_window == NULL )
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }


    }


    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if (ret == false)
    {
        return false;
    }

    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* moving_threats = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat = (moving_threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_xpos(500 + i*500);
            p_threat->set_ypos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);

            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_ojbs = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat = (threats_ojbs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_level.png", g_screen);
            p_threat->set_clips();
            p_threat->set_xpos(700 + i*1200);
            p_threat->set_ypos(250);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[])
{
    ImpTimer fps;

    if (InitData() == false)
    {
        return -1;
    }

    if(!LoadBackground())
    {
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap("map//map01.dat");
    game_map.LoadMapTiles(g_screen);


    MainObject p_player;
    p_player.LoadImg("img//walk_right.png", g_screen);
    p_player.set_clips();

    std::vector<ThreatsObject*> threats_list = MakeThreadList();


    bool is_quit = false;
    while (!is_quit)
    {
        fps.start();

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.GetMap();

        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->Show(g_screen);


            }
        }

        SDL_RenderPresent(g_screen);

        int imp_time = fps.get_ticks();
        int time_for_one_frame = 1000/FRAMES_PER_SECOND;
        if(imp_time < time_for_one_frame)
        {
            SDL_Delay(time_for_one_frame - imp_time);
        }


    }
    close();
    return 0;
};


