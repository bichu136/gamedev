#pragma once
#include "GameObject.h"
class Platform : public GameObject
{
private:
	int width_size;
	int height_size;
	int tile_corner_top_left;
	int tile_corner_top_right;
	int tile_corner_bottom_left;
	int tile_corner_bottom_right;
	int tile_edge_top;
	int tile_edge_left;
	int tile_edge_right;
	int tile_edge_bottom;
public:
	Platform(float x, float y);
	void Update(DWORD dt);
	int GetAnimationID(int i);
	int getCorrectAnimation();
	void AddAnimation(int id);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};