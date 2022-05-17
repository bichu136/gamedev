#include "Pipe.h"
#include "GlobalDefine.h"
Pipe::Pipe(float x, float y, int orientation, int size) :WoodenFloor(x, y, 0, 0)
{
    this->size = size;
    this->orientation = orientation;
    if (orientation == 0) {
        this->width = size;
        this->height = 2;
    }
    else {
        this->width = 2;
        this->height = size;
    }
    sprite_1 = 30125;
    sprite_2 = 30126;
    sprite_3 = 30127;
    sprite_4 = 30128;
    sprite_5 = 30225;
    sprite_6 = 30226;
    sprite_7 = 30227;
    sprite_8 = 30228;
    sprite_9 = -1;

}
void Pipe::Update(DWORD dt) {

}
int Pipe::GetAnimationID(int id) {
    return 0;
}
int Pipe::getCorrectAnimationID() {
    return 0;
}
void Pipe::AddAnimation(int id) {

}
void Pipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
    top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
    bottom = top + BRICK_WIDTH * height * SCALE_WIDTH;
    right = left + BRICK_WIDTH * width * SCALE_WIDTH;


}

int Pipe::getCorrectAnimation()
{
    return 0;
}
int Pipe::getCorrectSprite(int w_iter, int h_iter)
{
    if (orientation == 0) {
        //horizontal
        //3 4 7 8
        if (w_iter == 0){
            if (h_iter == 0) {
                return sprite_3;//sprite_4;
            }
            else {
                return sprite_7;//sprite_4;
            }
        }
        else {
            if (h_iter == 0) {
                return sprite_4;//sprite_4;
            }
            else {
                return sprite_8;//sprite_4;
            }
        }
    }
    else {
        //veritcal
        //1 2 5 6
        if (h_iter == height-1) {
            if (w_iter == 0) {
                return sprite_1;//sprite_4;
            }
            else {
                return sprite_2;//sprite_4;
            }
        }
        else {
            if (w_iter == 0) {
                return sprite_5;//sprite_4;
            }
            else {
                return sprite_6;//sprite_4;
            }
        }
    }
    
}
