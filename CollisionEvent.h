#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

class GameObject;


class CCollisionEvent;

class CollisionEvent
{
public:
	GameObject* srcObject;
	GameObject* des;

	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;
	CollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,
		GameObject* des = NULL, GameObject* src_obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->des = des;
		this->srcObject = src_obj;
		this->isDeleted = false;
	}
	int WasCollided() { return t >= 0.0f && t <= 1.0f; }

	static bool compare(const CollisionEvent* &a, CollisionEvent* &b)
	{
		return a->t < b->t;
	}
};

