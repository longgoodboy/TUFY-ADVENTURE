
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#include <vector>

#define GRAVITY_SPEED 1.5
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 10
#define PLAYER_HIGHT_VAL 18;


class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  enum WalkType
  {
    WALK_NONE = 0,
    WALK_RIGHT = 1,
    WALK_LEFT = 2,
  };


  bool LoadImg(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* des);
  void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
  void set_clips();

  void DoPlayer(Map& g_map);
  void CheckToMap(Map& g_map);
  void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
  void CenterEntityOnMap(Map& g_map);
  int get_x_pos() {return x_pos_;}
  int get_y_pos() {return y_pos_;}

  SDL_Rect GetRectFrame();
private:




  int frame_;
  int status_;

  SDL_Rect frame_clip_[6];
  Input input_type_;
  bool on_ground_;

  int map_x_;
  int map_y_;



  float x_val_;
  float y_val_;
  float x_pos_;
  float y_pos_;

  int width_frame_;
  int height_frame_;
  int come_back = 0;
};


#endif
