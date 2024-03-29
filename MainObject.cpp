#include "MainObject.h"
#include "commonfunc.h"
//const int PLAYER_WIDTH = 60;
//const int PLAYER_HEIGHT = 64;

#define  NUM_FRAME 6




MainObject::MainObject()
{
  frame_ = 0;
  x_pos_ = 0;
  y_pos_ = 0;
  x_val_ = 0;
  y_val_ = 0;
  inc_sp = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  status_ = -1;
  input_type_.left_ = 0;
  input_type_.right_ = 0;
  input_type_.down_ = 0;
  input_type_.jump_ = 0;
  input_type_.up_ = 0;
  on_ground_ = false;
  map_x_ = 0;
  map_y_ = 0;
  out_of_time = 0;
}

MainObject::~MainObject()
{
  Free();
}


bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    width_frame_ = rect_.w/6;
    height_frame_ = rect_.h;
  }

  return ret;
}

void MainObject::set_clips()
{
  //Clip the sprites
  if (width_frame_ > 0 && height_frame_ > 0)
  {
    frame_clip_[ 0 ].x = 0;
    frame_clip_[ 0 ].y = 0;
    frame_clip_[ 0 ].w = width_frame_;
    frame_clip_[ 0 ].h = height_frame_;

    frame_clip_[ 1 ].x = width_frame_;
    frame_clip_[ 1 ].y = 0;
    frame_clip_[ 1 ].w = width_frame_;
    frame_clip_[ 1 ].h = height_frame_;

    frame_clip_[ 2 ].x = width_frame_ * 2;
    frame_clip_[ 2 ].y = 0;
    frame_clip_[ 2 ].w = width_frame_;
    frame_clip_[ 2 ].h = height_frame_;

    frame_clip_[ 3 ].x = width_frame_ * 3;

    frame_clip_[ 3 ].y = 0;
    frame_clip_[ 3 ].w = width_frame_;
    frame_clip_[ 3 ].h = height_frame_;

    frame_clip_[ 4 ].x = width_frame_ * 4;
    frame_clip_[ 4 ].y = 0;
    frame_clip_[ 4 ].w = width_frame_;
    frame_clip_[ 4 ].h = height_frame_;

    frame_clip_[ 5 ].x = width_frame_ * 5;
    frame_clip_[ 5 ].y = 0;
    frame_clip_[ 5 ].w = width_frame_;
    frame_clip_[ 5 ].h = height_frame_;


  }
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

void MainObject::Show(SDL_Renderer* des)
{

  if (status_ == WALK_LEFT)
  {
      LoadImg("img//Walk_left.png", des);
  }
  else
  {
      LoadImg("img//Walk_right.png", des);
  }

  if((input_type_.left_ == 1 ||
    input_type_.right_ == 1  ))
  {
    frame_++;
  }
  else
  {
    frame_ = 0;
  }

  if( frame_ >= 6 )
  {
    frame_ = 0;
  }


    rect_.x = x_pos_ - map_x_ ;
    rect_.y = y_pos_ - map_y_ ;

    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};


    SDL_RenderCopy(des, p_object_, currentClip, &renderQuad );

}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{

  //If a key was pressed
  if( events.type == SDL_KEYDOWN )
  {
    //Set the velocity
    switch( events.key.keysym.sym )
    {
    case SDLK_RIGHT:
      {
        status_  = WALK_RIGHT;
        input_type_.right_ = 1;
        input_type_.left_ = 0;
        if (on_ground_ == true)
        {
            LoadImg("img//walk_right.png", screen);
        }
        else
        {
            LoadImg("img//walk_right.png", screen);
        }
        break;
      }
    case SDLK_LEFT:
      {
        status_ = WALK_LEFT;
        input_type_.left_ = 1;
        input_type_.right_ = 0;
        if (on_ground_ == true)
        {
            LoadImg("img//walk_left.png", screen);
        }
        else
        {
            LoadImg("img//walk_left.png", screen);
        }
        break;
      }
    case SDLK_UP:
        {
            input_type_.jump_ = 1;
        }
    }
  }
  //If a key was released
  else if( events.type == SDL_KEYUP )
  {

    ////Set the velocity
    switch( events.key.keysym.sym )
    {
    case SDLK_RIGHT:
      {
        input_type_.right_ = 0;

        break;
      }
    case SDLK_LEFT:
      {
        input_type_.left_ = 0;

        break;
      }
    case SDLK_UP:
      {
        input_type_.jump_ = 0;

        break;
      }
    }

  }
  else if (events.button.button == SDL_BUTTON_RIGHT)
    {
        input_type_.jump_ = 1;
    }

}

void MainObject::DoPlayer(Map& g_map)
{
    if (inc_sp == 0)
    {
        x_val_ = 0;
        y_val_ += 0.8;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= PLAYER_SPEED;
        }

        else if (input_type_.right_ == 1)
        {
            x_val_+= PLAYER_SPEED;
        }

        if (input_type_.jump_ == 1)
        {
            if (on_ground_ == true)
            {
                y_val_ = -PLAYER_HIGHT_VAL;
            }
            on_ground_ = false;
            input_type_.jump_ = 0;
        }
    }
    else if (inc_sp == 1)
    {
        x_val_ = 0;
        y_val_ += 0.8;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= 18;
            out_of_time -= 1;
        }

        else if (input_type_.right_ == 1)
        {
            x_val_+= 18;
            out_of_time -= 1;
        }

        if (input_type_.jump_ == 1)
        {
            if (on_ground_ == true)
            {
                y_val_ = -22;
            }

            on_ground_ = false;
            input_type_.jump_ = 0;
            out_of_time -= 1;
        }
        if (out_of_time == 0) inc_sp = 0;
    }

        CheckToMap(g_map);
        CenterEntityOnMap(g_map);



}

void MainObject::CenterEntityOnMap(Map& g_map)
{
    g_map.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if (g_map.start_x_ < 0)
  {
    g_map.start_x_ = 0;
  }

  else if (g_map.start_x_ + SCREEN_WIDTH >= g_map.max_x_)
  {
    g_map.start_x_= g_map.max_x_ - SCREEN_WIDTH;
  }

  g_map.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);

  if (g_map.start_y_ < 0)
  {
    g_map.start_y_ = 0;
  }

  else if (g_map.start_y_+ SCREEN_HEIGHT >= g_map.max_y_)
  {
    g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
  }
}

void MainObject::CheckToMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //check chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ )/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {

        if (x_val_ > 0)
        {
            int val1 = g_map.tile[y1][x2];
            int val2 = g_map.tile[y2][x2];
            if (val1 == 4 || val2 == 4)
            {
                g_map.tile[y1][x2] = 0;
                g_map.tile[y2][x2] = 0;
                inc_sp = 1;
                out_of_time = 100;
            }


            if (g_map.tile[y1][x2] != BLANK_TILE || g_map.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            int val1 = g_map.tile[y1][x1];
            int val2 = g_map.tile[y2][x1];
            if (val1 == 4 || val2 == 4)
            {
                g_map.tile[y1][x1] = 0;
                g_map.tile[y2][x1] = 0;
                inc_sp = 1;
                out_of_time = 100;
            }

            if (g_map.tile[y1][x1] != BLANK_TILE || g_map.tile[y2][x1] != BLANK_TILE)
            {
                x_pos_ = (x1 + 1)*TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //check chieu doc
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = x_pos_ / TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            int val1 = g_map.tile[y2][x1];
            int val2 = g_map.tile[y2][x2];
            if (val1 == 4 || val2 == 4)
            {
                g_map.tile[y2][x1] = 0;
                g_map.tile[y2][x2] = 0;
                inc_sp = 1;
                out_of_time = 100;
            }
            if (g_map.tile[y2][x1] != BLANK_TILE || g_map.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = g_map.tile[y1][x1];
            int val2 = g_map.tile[y1][x2];
            if (val1 == 4 || val2 == 4)
            {
                g_map.tile[y1][x1] = 0;
                g_map.tile[y1][x2] = 0;
                inc_sp = 1;
                out_of_time = 100;
            }
            if (g_map.tile[y1][x1] != BLANK_TILE || g_map.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = (y1 + 1)*TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > g_map.max_x_)
    {
        x_pos_ = g_map.max_x_ - width_frame_ - 1;
    }
    if (y_pos_ > g_map.max_y_)
    {
        if(MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK)
                   {
                       SDL_Quit();
                   }

    }
}
