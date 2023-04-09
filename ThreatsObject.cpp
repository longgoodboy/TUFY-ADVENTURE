

#include "ThreatsObject.h"



ThreatsObject::ThreatsObject()
{
  rect_.x = SCREEN_WIDTH;
  rect_.y = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  x_val_ = 0;
  y_val_ = 0;
  //is_alive_ = false;

  x_pos_ = 0;
  y_pos_ = 0;
  on_ground_ = 0;
  think_time_ = 0;
  input_type_.left_ = 1;
  frame_ = 0;
  type_move_ = STATIC_TH;
  input_type_.left_ = 0;
}

ThreatsObject::~ThreatsObject()
{

}

SDL_Rect ThreatsObject::GetRectFrame()
{
  SDL_Rect rect;
  rect.x = rect_.x;
  rect.y = rect_.y;
  rect.w = rect_.w/NUM_FRAME;
  rect.h = rect_.h;

  return rect;
}








void ThreatsObject::InitPlayer()
{
  //x_pos_ = SCREEN_WIDTH - 400;
  //y_pos_ = SCREEN_HEIGHT*0.5;
  x_val_ = 0;
  y_val_ = 0;

  if (x_pos_ > 256)
  {
      x_pos_ -= 256;
      animation_a_ -= 256;
      animation_b_ -= 256;
  }
  else
      x_pos_ = 0;
  y_pos_ = 0;
  think_time_ = 0;
  input_type_.left_ = 1;

}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    width_frame_ = rect_.w/NUM_FRAME;
    height_frame_ = rect_.h;
  }

  return ret;
}


void ThreatsObject::set_clips()
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

    frame_clip_[ 6 ].x = width_frame_ * 6;
    frame_clip_[ 6 ].y = 0;
    frame_clip_[ 6 ].w = width_frame_;
    frame_clip_[ 6 ].h = height_frame_;

    frame_clip_[ 7 ].x = width_frame_ * 7;
    frame_clip_[ 7 ].y = 0;
    frame_clip_[ 7 ].w = width_frame_;
    frame_clip_[ 7 ].h = height_frame_;
  }
}


void ThreatsObject::SetAnimationPos(const int& pos_x_a, const int& pos_x_b)
{
  animation_b_ = pos_x_b;
  animation_a_ = pos_x_a;
}


void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
  if (type_move_ == STATIC_TH)
  {
    ;//
  }
  else
  {
    if (on_ground_ == true)
    {
      if (x_pos_ > animation_b_)
      {
        input_type_.left_ = 1;
        input_type_.right_ = 0;
        LoadImg("img//threat_left.png", screen);
      }
      else if (x_pos_ < animation_a_)
      {
        input_type_.right_ = 1;
        input_type_.left_ = 0;
        LoadImg("img//threat_right.png", screen);
      }
    }
    else
    {
        if (input_type_.left_ == 1)
        {
            LoadImg("img//threat_left.png", screen);
        }
    }
  }
}

void ThreatsObject::DoPlayer(Map& g_map)
{
  if (think_time_ == 0)
  {
    x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

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
      if (on_ground_ == 1)
      {
        y_val_ = -PLAYER_HIGHT_VAL;
      }

      input_type_.jump_ = 0;
    }

    CheckToMap(g_map);

    //CenterEntityOnMap(g_map);
  }

  if (think_time_ > 0)
  {
    think_time_--;

    if (think_time_ == 0)
    {
      InitPlayer();
    }
  }
}

void ThreatsObject::CenterEntityOnMap(Map& g_map)
{
  g_map.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);

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

void ThreatsObject::CheckToMap(Map& g_map)
{
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  on_ground_ = 0;

  //Check Horizontal
  int height_min =   height_frame_ ;//SDLCommonFunc::GetMin(height_frame_, TILE_SIZE);

  /*
           x1,y1***x2
           *       *
           *       *
           *       *
           *y2******

  */
  x1 = (x_pos_ + x_val_) / TILE_SIZE;
  x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

  y1 = (y_pos_) / TILE_SIZE;
  y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

  // Check x1, x2 with full width of map
  // Check y1, y2 with full heigth of map
  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (x_val_ > 0) // when object is moving by right  ===>
    {
      // Check current position of map. It is not blank_tile.
      if ((g_map.tile[y1][x2] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
      {
        // Fixed post of object at current post of map.
        // => Cannot moving when press button
        x_pos_ = x2 * TILE_SIZE;
        x_pos_ -= width_frame_ + 1;
        x_val_ = 0; // cannot moving
      }
    }
    else if (x_val_ < 0) // When moving by left    <====
    {
      if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
      {
        x_pos_ = (x1 + 1) * TILE_SIZE;
        x_val_ = 0;
      }
    }
  }


  // Check vertical
  int width_min = width_frame_ ;//SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

  x1 = (x_pos_) / TILE_SIZE;
  x2 = (x_pos_ + width_min) / TILE_SIZE;

  y1 = (y_pos_ + x_val_) / TILE_SIZE;
  y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (y_val_ > 0)
    {
      //Similar for vertical
      if ((g_map.tile[y2][x1] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
      {
        y_pos_ = y2 * TILE_SIZE;
        y_pos_ -= height_frame_;

        y_val_ = 0;

        on_ground_ = 1;
      }
    }
    else if (y_val_ < 0)
    {
      if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y1][x2] != BLANK_TILE))
      {
        y_pos_ = (y1 + 1) * TILE_SIZE;

        y_val_ = 0;
      }
    }
  }

  //If there is not collision with map tile.
  x_pos_ += x_val_;
  y_pos_ += y_val_;

  if (x_pos_ < 0)
  {
    x_pos_ = 0;
  }
  else if (x_pos_ + width_frame_ >= g_map.max_x_)
  {
    x_pos_ = g_map.max_x_ - width_frame_ - 1;
  }

  if (y_pos_ > g_map.max_y_)
  {
    think_time_ = 60;
  }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
  if (think_time_ == 0)
  {
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_- map_y_;
      frame_++;
      if( frame_ >= 8 )
      {
        frame_ = 0;
      }

      SDL_Rect* currentClip = &frame_clip_[frame_];
      SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
      if (currentClip != NULL)
      {
         renderQuad.w = currentClip->w;
         renderQuad.h = currentClip->h;
      }

      SDL_RenderCopy(des, p_object_, currentClip, &renderQuad );
  }
}
