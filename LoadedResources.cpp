#include "LoadedResources.h"
#include"SpriteManage.h"
#include"TextureManager.h"
#include"AnimationManage.h"
#include "GlobalDefine.h"
#include "debug.h"

#define BLOCK_PUSH_FACTOR 0.004f
LoadedResources* LoadedResources::__instance = NULL;
void LoadedResources::_SweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float& t, float& nx, float& ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;// entry src.left to des.right, exit src.right to des.left
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	//get next frame bounding box;
	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;
	//check if next freme is collide with des bb or not.
	if (br < sl || bl > sr || bb < st || bt > sb) return;
	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision
	
	//getting current frame
	//if speed of between 2 obj is not the same
	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	//if the speed is the same then time to collide is infinite
	//if the spped is not the same, find time to collide
	if (dx == 0)
	{
		tx_entry = -9999999.0f;
		tx_exit = 99999999.0f;
	}
	else
	{
		//if not
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999.0f;
		ty_exit = 99999999999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}
	//using time to check if 2 object is collide or not with only entry?
	//DebugOutTitle(L"something: %0.5f,%0.5f",tx_entry,ty_entry);
	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;
	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);
	if (t_entry > t_exit) return;
	//return result;
	t = t_entry;
	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}
CollisionEvent* LoadedResources::SweptAABB(GameObject* objSrc, DWORD dt, GameObject* objDest)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;			// returned value from Swept AABB

	//getting speed of objecSrc
	float mvx, mvy;
	objSrc->GetSpeed(mvx, mvy);
	float mdx = mvx ;
	float mdy = mvy ;

	//getting speed of des
	float svx, svy;
	objDest->GetSpeed(svx, svy);
	float sdx = svx;
	float sdy = svy;

	//dvx, dvy
	float dvx = mdx - sdx;
	float dvy = mdy - sdy;
	objSrc->GetBoundingBox(ml, mt, mr, mb);
	objDest->GetBoundingBox(sl, st, sr, sb);
	_SweptAABB(
		ml, mt, mr, mb, dvx, dvy, sl, st, sr, sb, t, nx, ny);
	return new CollisionEvent(t, nx, ny, dvx, dvy, objDest, objSrc);
}
void LoadedResources::Scan(GameObject* objSrc, 
	                       DWORD dt, 
	                       std::vector<GameObject*>* objDests, 
	                       std::vector<CollisionEvent*>& coEvents)
{
	for (UINT i = 0; i < objDests->size(); i++)
	{
		CollisionEvent* e = LoadedResources::SweptAABB(objSrc, dt, objDests->at(i));
		if (e->WasCollided() == 1)
			coEvents.push_back(e);
		else
			delete e;
	}
}
void LoadedResources::Filter(GameObject* objSrc, 
	                         std::vector<CollisionEvent*> &coEvents, 
	                         CollisionEvent* &colX, 
	                         CollisionEvent* &colY, 
	                         int filterBlock, 
	                         int filterX, 
	                         int filterY)
{
	float min_tx, min_ty;

	int min_ix = -1;
	int min_iy = -1;
	for (int i = 0; i < coEvents.size(); i++) {
		CollisionEvent* c = coEvents.at(i);
		//check Events is available or not
		//if (c->isDeleted) continue;
		//if (c->obj->IsDeleted()) continue;
		//// ignore collision event with object having IsBlocking = 0 (like coin, mushroom, etc)
		if (filterBlock == 1 && !c->srcObject->isBlocking())
		{
			continue;
		}
		if (filterX == 1 && c->nx != 0){
			min_ix = i;
		}
		if (filterY == 1 && c->ny != 0) {
			min_iy = i;
		}
		
	}
	CollisionEvent* c1 = NULL;
	CollisionEvent* c2 = NULL;
	if (min_ix >= 0) c1 = coEvents[min_ix];
	if (min_iy >= 0) c2 = coEvents[min_iy];

	colY = c2;
	colX = c1;

}
LoadedResources* LoadedResources::getInstance()
{
	if (__instance == NULL) __instance = new LoadedResources();
	return __instance;
}

void LoadedResources::LoadResources()
{
	SpriteManage* sm = SpriteManage::getInstance();
	TextureManager* tm = TextureManager::getInstance();
	AnimationManage* am = AnimationManage::getInstance();
	

	Animation* pAni;
	//idle animation;
	tm->Add(0, MARIO_TEX);
	tm->Add(1, ENEMY_TEX);
	tm->Add(2, MISC_TEX);
	tm->Add(3, TILE_TEX);
	//mario line 1 sprite
	sm->Add(0,0, 0, 445, 1597, tm->getTextureWithId(0));
	sm->Add(1101,   0, 0,  24, 19, tm->getTextureWithId(0));
	sm->Add(1102,  30, 0,  54, 19, tm->getTextureWithId(0));
	sm->Add(1103,  60, 0,  84, 19, tm->getTextureWithId(0));
	sm->Add(1104,  90, 0, 114, 19, tm->getTextureWithId(0));
	sm->Add(1105, 120, 0, 144, 19, tm->getTextureWithId(0));
	sm->Add(1106, 150, 0, 174, 19, tm->getTextureWithId(0));
	sm->Add(1107, 180, 0, 204, 19, tm->getTextureWithId(0));
	sm->Add(1108, 210, 0, 234, 19, tm->getTextureWithId(0));
	sm->Add(1109, 240, 0, 264, 19, tm->getTextureWithId(0));
	sm->Add(1110, 270, 0, 294, 19, tm->getTextureWithId(0));
	sm->Add(1111, 300, 0, 324, 19, tm->getTextureWithId(0));
	sm->Add(1112, 330, 0, 354, 19, tm->getTextureWithId(0));
	sm->Add(1113, 360, 0, 384, 19, tm->getTextureWithId(0));
	sm->Add(1114, 390, 0, 414, 19, tm->getTextureWithId(0));
	sm->Add(1115, 420, 0, 444, 19, tm->getTextureWithId(0));
	//mario line 2 sprite
	sm->Add(1201,   0, 40,  24, 59, tm->getTextureWithId(0));
	sm->Add(1202,  30, 40,  54, 59, tm->getTextureWithId(0));
	sm->Add(1203,  60, 40,  84, 59, tm->getTextureWithId(0));
	sm->Add(1204,  90, 40, 114, 59, tm->getTextureWithId(0));
	sm->Add(1205, 120, 40, 144, 59, tm->getTextureWithId(0));
	sm->Add(1206, 150, 40, 174, 59, tm->getTextureWithId(0));
	sm->Add(1207, 180, 40, 204, 59, tm->getTextureWithId(0));
	sm->Add(1208, 210, 40, 234, 59, tm->getTextureWithId(0));
	sm->Add(1209, 240, 40, 264, 59, tm->getTextureWithId(0));
	sm->Add(1210, 270, 40, 294, 59, tm->getTextureWithId(0));
	sm->Add(1211, 300, 40, 324, 59, tm->getTextureWithId(0));
	sm->Add(1212, 330, 40, 354, 59, tm->getTextureWithId(0));
	sm->Add(1213, 360, 40, 384, 59, tm->getTextureWithId(0));
	sm->Add(1214, 390, 40, 414, 59, tm->getTextureWithId(0));
	sm->Add(1215, 420, 40, 444, 59, tm->getTextureWithId(0));
	//line 3 sprite
	sm->Add(1301,  0,  80,  24, 99, tm->getTextureWithId(0));
	sm->Add(1302,  30, 80,  54, 99, tm->getTextureWithId(0));
	sm->Add(1303,  60, 80,  84, 99, tm->getTextureWithId(0));
	sm->Add(1304,  90, 80, 114, 99, tm->getTextureWithId(0));
	sm->Add(1305, 120, 80, 144, 99, tm->getTextureWithId(0));
	sm->Add(1306, 150, 80, 174, 99, tm->getTextureWithId(0));
	sm->Add(1307, 180, 80, 204, 99, tm->getTextureWithId(0));
	sm->Add(1308, 210, 80, 234, 99, tm->getTextureWithId(0));
	sm->Add(1309, 240, 80, 264, 99, tm->getTextureWithId(0));
	sm->Add(1310, 270, 80, 294, 99, tm->getTextureWithId(0));
	sm->Add(1311, 300, 80, 324, 99, tm->getTextureWithId(0));
	sm->Add(1312, 330, 80, 354, 99, tm->getTextureWithId(0));
	sm->Add(1313, 360, 80, 384, 99, tm->getTextureWithId(0));
	sm->Add(1314, 390, 80, 414, 99, tm->getTextureWithId(0));
	sm->Add(1315, 420, 80, 444, 99, tm->getTextureWithId(0));
	//line 4 sprite
	sm->Add(1401,   0, 120,  24, 139, tm->getTextureWithId(0));
	sm->Add(1402,  30, 120,  54, 139, tm->getTextureWithId(0));
	sm->Add(1403,  60, 120,  84, 139, tm->getTextureWithId(0));
	sm->Add(1404,  90, 120, 114, 139, tm->getTextureWithId(0));
	sm->Add(1405, 120, 120, 144, 139, tm->getTextureWithId(0));
	sm->Add(1406, 150, 120, 174, 139, tm->getTextureWithId(0));
	sm->Add(1407, 180, 120, 204, 139, tm->getTextureWithId(0));
	sm->Add(1408, 210, 120, 234, 139, tm->getTextureWithId(0));
	sm->Add(1409, 240, 120, 264, 139, tm->getTextureWithId(0));
	sm->Add(1410, 270, 120, 294, 139, tm->getTextureWithId(0));
	sm->Add(1411, 300, 120, 324, 139, tm->getTextureWithId(0));
	sm->Add(1412, 330, 120, 354, 139, tm->getTextureWithId(0));
	sm->Add(1413, 360, 120, 384, 139, tm->getTextureWithId(0));
	sm->Add(1414, 390, 120, 414, 139, tm->getTextureWithId(0));
	sm->Add(1415, 420, 120, 444, 139, tm->getTextureWithId(0));


	// misc sprite.
	//golden brick
	sm->Add(2101, 300, 135, 315, 150, tm->getTextureWithId(2));
	sm->Add(2102, 318, 135, 333, 150, tm->getTextureWithId(2));
	sm->Add(2103, 336, 135, 351, 150, tm->getTextureWithId(2));
	sm->Add(2104, 354, 135, 369, 150, tm->getTextureWithId(2));
	sm->Add(2105, 372, 135, 387, 150, tm->getTextureWithId(2));

	// tile
	for (int i = 0; i < 42; i++) {
		for (int j = 0; i < 42; i++) {
			int _top = 2*(i+1) + (i * 16);
			int _left = 2 * (i + 1) + (i * 16);
			int _right = _left + 16;
			int _bottom = _top + 16;
			sm->Add(30000 + i * 100 + j, _top, _left, _right, _bottom,tm->getTextureWithId(3));
		}
	}
	//idle face left
	pAni = new Animation(100);
	pAni->Add(1107,5);
	am->Add(100, pAni);
	//idle face right
	pAni = new Animation(100);
	pAni->Add(1109, 5);
	am->Add(101, pAni);

	//walk face left
	pAni = new Animation(100);
	pAni->Add(1105, 5);
	pAni->Add(1107, 5);
	am->Add(102, pAni);
	
	//walk face right
	pAni = new Animation(100);
	pAni->Add(1111, 5);
	pAni->Add(1109, 5);
	am->Add(103, pAni);

	//normal jump face left
	pAni = new Animation(100);
	pAni->Add(1302, 5);
	am->Add(104, pAni);

	//normal jump face right
	pAni = new Animation(100);
	pAni->Add(1314, 5);
	am->Add(105, pAni);

	//p speed face left
	pAni = new Animation(100);
	pAni->Add(1301, 5);
	pAni->Add(1106, 5);
	am->Add(106, pAni);
	//p speed face right
	pAni = new Animation(100);
	pAni->Add(1110, 3);
	pAni->Add(1315, 3);
	am->Add(107, pAni);
	//break left
	pAni = new Animation(100);
	pAni->Add(1115, 3);
	am->Add(108, pAni);
	//break right
    pAni = new Animation(100);
	pAni->Add(1101, 3);
	am->Add(109, pAni);

	Animation* pBrickAnimation = new Animation(100);
	pBrickAnimation->Add(2101, 3);
	pBrickAnimation->Add(2102, 3);
	pBrickAnimation->Add(2103, 3);
	pBrickAnimation->Add(2104, 3);
	pBrickAnimation->Add(2105, 3);
	am->Add(201, pBrickAnimation);


	Mario = new PlayableCharacter(20.f,200.0f);
	
	/*Mario->AddAnimation(100);
	Mario->AddAnimation(101);
	Mario->AddAnimation(102);
	Mario->AddAnimation(103);
	Mario->AddAnimation(104);
	Mario->AddAnimation(105);
	Mario->AddAnimation(106);
	Mario->AddAnimation(107);*/
	for (int i = 0; i < 100; i++){
		stage_blocks.push_back(new Platform(30.0f * (i)+15.0f, 15.0f));
		stage_blocks[i]->AddAnimation(201);
	}
}

void LoadedResources::Update(DWORD dt)
{
	Mario->Update(dt);
	//world stuff
	// -  collsion check between varies gameobjects.
	// - moving gameobject according to their speed.
	std::vector<CollisionEvent* > collisionEvents;
	//std::vector<CollisionEvent*> &coEvents
	CollisionEvent* colX = NULL;
	CollisionEvent* colY = NULL;
	collisionEvents.clear();
	// check for everything 
	if (Mario->isCollidable()) {
		Scan(Mario, dt, &stage_blocks, collisionEvents);
	}
	//no colision
	if (collisionEvents.size() == 0) {
		Mario->OnNoCollision();
	}
	else {
		//get who have collision first in X axis and Y axis

		Filter(Mario, collisionEvents, colX, colY);
		float x, y, vx, vy, dx, dy;
		Mario->GetPosition(x, y);
		Mario->GetSpeed(vx, vy);
		dx = vx ;
		dy = vy ;

		if (colX != NULL && colY != NULL)
		{
			if (colY->t < colX->t)	// was collision on Y first ?
			{
				y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
				Mario->SetPosition(x, y);

				Mario->onCollisionWith(colY);

				//
				// see if after correction on Y, is there still a collision on X ? 
				//
				CollisionEvent* colX_other = NULL;

				//
				// check again if there is true collision on X 
				//
				colX->isDeleted = true;		// remove current collision event on X

				// replace with a new collision event using corrected location 
				collisionEvents.push_back(SweptAABB(Mario, dt, colX->des));

				// re-filter on X only
				Filter(Mario, collisionEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);

				if (colX_other != NULL)
				{
					x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
					Mario->onCollisionWith(colX_other);
				}
				else
				{
					x += dx;
				}
			}
			else // collision on X first
			{
				x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				Mario->SetPosition(x, y);

				Mario->onCollisionWith(colX);

				//
				// see if after correction on X, is there still a collision on Y ? 
				//
				CollisionEvent* colY_other = NULL;

				//
				// check again if there is true collision on Y
				//
				colY->isDeleted = true;		// remove current collision event on Y

				// replace with a new collision event using corrected location 
				collisionEvents.push_back(SweptAABB(Mario, dt, colY->des));

				// re-filter on Y only
				Filter(Mario, collisionEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);

				if (colY_other != NULL)
				{
					y += colY_other->t * dy + colY_other->ny * BLOCK_PUSH_FACTOR;
					Mario->onCollisionWith(colY_other);
				}
				else
				{
					y += dy;
				}
			}
		}
		else
			if (colX != NULL)
			{
				x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				y += dy;
				Mario->onCollisionWith(colX);
			}
			else
				if (colY != NULL)
				{
					x += dx;
					y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
					SweptAABB(Mario, dt, colY->des);
					Mario->onCollisionWith(colY);
				}
				else // both colX & colY are NULL 
				{
					x += dx;
					y += dy;
				}

		Mario->SetPosition(x, y);
	}

	////
	//// Scan all non-blocking collisions for further collision logic
	////
	//for (UINT i = 0; i < coEvents.size(); i++)
	//{
	//	LPCOLLISIONEVENT e = coEvents[i];
	//	if (e->isDeleted) continue;
	//	if (e->obj->IsBlocking()) continue;  // blocking collisions were handled already, skip them

	//	objSrc->OnCollisionWith(e);
	//}


	for (UINT i = 0; i < collisionEvents.size(); i++) delete collisionEvents[i];
}
