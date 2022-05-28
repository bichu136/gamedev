#include "LoadedResources.h"
#include"SpriteManage.h"
#include"TextureManager.h"
#include"AnimationManage.h"
#include "GlobalDefine.h"
#include "RedKooba.h"
#include "debug.h"
#include "Mushroom.h"
#include "Plant.h"

#define BLOCK_PUSH_FACTOR 1.50f
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
	//DebugOutTitle(L"something: %0.5f,%0.5f",mb,mt);
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

		if (e->WasCollided() == 1) {
			coEvents.push_back(e);
			//DebugOutTitle(L"%d", i);
		}
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
void LoadedResources::loadMarioSprite()
{
	SpriteManage* sm = SpriteManage::getInstance();
	TextureManager* tm = TextureManager::getInstance();
	//mario line 1 sprite
	sm->Add(0, 0, 0, 445, 1597, tm->getTextureWithId(0));
	sm->Add(10101, 0, 0, 24, 19, tm->getTextureWithId(0));
	sm->Add(10102, 30, 0, 54, 19, tm->getTextureWithId(0));
	sm->Add(10103, 60, 0, 84, 19, tm->getTextureWithId(0));
	sm->Add(10104, 90, 0, 114, 19, tm->getTextureWithId(0));
	sm->Add(10105, 120, 0, 144, 19, tm->getTextureWithId(0));
	sm->Add(10106, 150, 0, 174, 19, tm->getTextureWithId(0));
	sm->Add(10107, 180, 0, 204, 19, tm->getTextureWithId(0));
	sm->Add(10108, 210, 0, 234, 19, tm->getTextureWithId(0));
	sm->Add(10109, 240, 0, 264, 19, tm->getTextureWithId(0));
	sm->Add(10110, 270, 0, 294, 19, tm->getTextureWithId(0));
	sm->Add(10111, 300, 0, 324, 19, tm->getTextureWithId(0));
	sm->Add(10112, 330, 0, 354, 19, tm->getTextureWithId(0));
	sm->Add(10113, 360, 0, 384, 19, tm->getTextureWithId(0));
	sm->Add(10114, 390, 0, 414, 19, tm->getTextureWithId(0));
	sm->Add(10115, 420, 0, 444, 19, tm->getTextureWithId(0));
	//mario line 2 sprite
	sm->Add(10201, 0, 40, 24, 59, tm->getTextureWithId(0));
	sm->Add(10202, 30, 40, 54, 59, tm->getTextureWithId(0));
	sm->Add(10203, 60, 40, 84, 59, tm->getTextureWithId(0));
	sm->Add(10204, 90, 40, 114, 59, tm->getTextureWithId(0));
	sm->Add(10205, 120, 40, 144, 59, tm->getTextureWithId(0));
	sm->Add(10206, 150, 40, 174, 59, tm->getTextureWithId(0));
	sm->Add(10207, 180, 40, 204, 59, tm->getTextureWithId(0));
	sm->Add(10208, 210, 40, 234, 59, tm->getTextureWithId(0));
	sm->Add(10209, 240, 40, 264, 59, tm->getTextureWithId(0));
	sm->Add(10210, 270, 40, 294, 59, tm->getTextureWithId(0));
	sm->Add(10211, 300, 40, 324, 59, tm->getTextureWithId(0));
	sm->Add(10212, 330, 40, 354, 59, tm->getTextureWithId(0));
	sm->Add(10213, 360, 40, 384, 59, tm->getTextureWithId(0));
	sm->Add(10214, 390, 40, 414, 59, tm->getTextureWithId(0));
	sm->Add(10215, 420, 40, 444, 59, tm->getTextureWithId(0));
	//line 3 sprite
	sm->Add(10301, 0, 80, 24, 99, tm->getTextureWithId(0));
	sm->Add(10302, 30, 80, 54, 99, tm->getTextureWithId(0));
	sm->Add(10303, 60, 80, 84, 99, tm->getTextureWithId(0));
	sm->Add(10304, 90, 80, 114, 99, tm->getTextureWithId(0));
	sm->Add(10305, 120, 80, 144, 99, tm->getTextureWithId(0));
	sm->Add(10306, 150, 80, 174, 99, tm->getTextureWithId(0));
	sm->Add(10307, 180, 80, 204, 99, tm->getTextureWithId(0));
	sm->Add(10308, 210, 80, 234, 99, tm->getTextureWithId(0));
	sm->Add(10309, 240, 80, 264, 99, tm->getTextureWithId(0));
	sm->Add(10310, 270, 80, 294, 99, tm->getTextureWithId(0));
	sm->Add(10311, 300, 80, 324, 99, tm->getTextureWithId(0));
	sm->Add(10312, 330, 80, 354, 99, tm->getTextureWithId(0));
	sm->Add(10313, 360, 80, 384, 99, tm->getTextureWithId(0));
	sm->Add(10314, 390, 80, 414, 99, tm->getTextureWithId(0));
	sm->Add(10315, 420, 80, 444, 99, tm->getTextureWithId(0));
	//line 4 sprite
	sm->Add(10401, 0, 120, 24, 139, tm->getTextureWithId(0));
	sm->Add(10402, 30, 120, 54, 139, tm->getTextureWithId(0));
	sm->Add(10403, 60, 120, 84, 139, tm->getTextureWithId(0));
	sm->Add(10404, 90, 120, 114, 139, tm->getTextureWithId(0));
	sm->Add(10405, 120, 120, 144, 139, tm->getTextureWithId(0));
	sm->Add(10406, 150, 120, 174, 139, tm->getTextureWithId(0));
	sm->Add(10407, 180, 120, 204, 139, tm->getTextureWithId(0));
	sm->Add(10408, 210, 120, 234, 139, tm->getTextureWithId(0));
	sm->Add(10409, 240, 120, 264, 139, tm->getTextureWithId(0));
	sm->Add(10410, 270, 120, 294, 139, tm->getTextureWithId(0));
	sm->Add(10411, 300, 120, 324, 139, tm->getTextureWithId(0));
	sm->Add(104012, 330, 120, 354, 139, tm->getTextureWithId(0));
	sm->Add(10413, 360, 120, 384, 139, tm->getTextureWithId(0));
	sm->Add(10414, 390, 120, 414, 139, tm->getTextureWithId(0));
	sm->Add(10415, 420, 120, 444, 139, tm->getTextureWithId(0));
	//line 5 to 22 sprite
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 15; j++) {
			sm->Add(10000+(i+5)*100+j+1, j*30, (i*40)+154, (j*30)+24, (i*40) + 182, tm->getTextureWithId(0));
		}
	}
	//sm->Add(1501, 0, 154, 24, 182, tm->getTextureWithId(0));
	//sm->Add(1502, 30, 154, 54, 182, tm->getTextureWithId(0));
	//sm->Add(1503, 60, 154, 84, 182, tm->getTextureWithId(0));
	//sm->Add(1504, 90, 154, 114, 182, tm->getTextureWithId(0));
	//sm->Add(1505, 120, 154, 144, 182, tm->getTextureWithId(0));
	//sm->Add(1506, 150, 154, 174, 182, tm->getTextureWithId(0));
	//sm->Add(1507, 180, 154, 204, 182, tm->getTextureWithId(0));
	//sm->Add(1508, 210, 154, 234, 182, tm->getTextureWithId(0));
	//sm->Add(1509, 240, 154, 264, 182, tm->getTextureWithId(0));
	//sm->Add(1510, 270, 154, 294, 182, tm->getTextureWithId(0));
	//sm->Add(1511, 300, 154, 324, 182, tm->getTextureWithId(0));
	//sm->Add(1512, 330, 154, 354, 182, tm->getTextureWithId(0));
	//sm->Add(1513, 360, 154, 384, 182, tm->getTextureWithId(0));
	//sm->Add(1514, 390, 154, 414, 182, tm->getTextureWithId(0));
	//sm->Add(1515, 420, 154, 444, 182, tm->getTextureWithId(0));
	////line 6 sprite
	//sm->Add(1501, 0, 194, 24, 222, tm->getTextureWithId(0));
	//sm->Add(1502, 30, 194, 54, 222, tm->getTextureWithId(0));
	//sm->Add(1503, 60, 194, 84, 222, tm->getTextureWithId(0));
	//sm->Add(1504, 90, 194, 114, 222, tm->getTextureWithId(0));
	//sm->Add(1505, 120, 194, 144, 222, tm->getTextureWithId(0));
	//sm->Add(1506, 150, 194, 174, 222, tm->getTextureWithId(0));
	//sm->Add(1507, 180, 194, 204, 222, tm->getTextureWithId(0));
	//sm->Add(1508, 210, 194, 234, 222, tm->getTextureWithId(0));
	//sm->Add(1509, 240, 194, 264, 222, tm->getTextureWithId(0));
	//sm->Add(1510, 270, 194, 294, 222, tm->getTextureWithId(0));
	//sm->Add(1511, 300, 194, 324, 222, tm->getTextureWithId(0));
	//sm->Add(1512, 330, 194, 354, 222, tm->getTextureWithId(0));
	//sm->Add(1513, 360, 194, 384, 222, tm->getTextureWithId(0));
	//sm->Add(1514, 390, 194, 414, 222, tm->getTextureWithId(0));
	//sm->Add(1515, 420, 194, 444, 222, tm->getTextureWithId(0));
	////line 8 sprite
	//sm->Add(1501, 0, 194, 24, 222, tm->getTextureWithId(0));
	//sm->Add(1502, 30, 194, 54, 222, tm->getTextureWithId(0));
	//sm->Add(1503, 60, 194, 84, 222, tm->getTextureWithId(0));
	//sm->Add(1504, 90, 194, 114, 222, tm->getTextureWithId(0));
	//sm->Add(1505, 120, 194, 144, 222, tm->getTextureWithId(0));
	//sm->Add(1506, 150, 194, 174, 222, tm->getTextureWithId(0));
	//sm->Add(1507, 180, 194, 204, 222, tm->getTextureWithId(0));
	//sm->Add(1508, 210, 194, 234, 222, tm->getTextureWithId(0));
	//sm->Add(1509, 240, 194, 264, 222, tm->getTextureWithId(0));
	//sm->Add(1510, 270, 194, 294, 222, tm->getTextureWithId(0));
	//sm->Add(1511, 300, 194, 324, 222, tm->getTextureWithId(0));
	//sm->Add(1512, 330, 194, 354, 222, tm->getTextureWithId(0));
	//sm->Add(1513, 360, 194, 384, 222, tm->getTextureWithId(0));
	//sm->Add(1514, 390, 194, 414, 222, tm->getTextureWithId(0));
	//sm->Add(1515, 420, 194, 444, 222, tm->getTextureWithId(0));
	
}
void LoadedResources::createMarioAnimation()
{
	createSmallMarioAnimation();
	createBigMarioAnimation();
	createFireMarioAnimation();
	createTanukiMarioAnimation();
}
void LoadedResources::createFireMarioAnimation()
{
	AnimationManage* am = AnimationManage::getInstance();
	Animation* pAni;
	//idle face left
	pAni = new Animation(100);
	pAni->Add(11107, 5);
	am->Add(FIRE_MARIO_STATE_IDLE_LEFT, pAni);
	//idle face right
	pAni = new Animation(100);
	pAni->Add(11109, 5);
	am->Add(FIRE_MARIO_STATE_IDLE_RIGHT, pAni);

	//walk face left
	pAni = new Animation(100);
	pAni->Add(11105, 5);
	pAni->Add(11107, 5);
	am->Add(FIRE_MARIO_STATE_WALK_LEFT, pAni);

	//walk face right
	pAni = new Animation(100);
	pAni->Add(11111, 5);
	pAni->Add(11109, 5);
	am->Add(FIRE_MARIO_STATE_WALK_RIGHT, pAni);

	//normal jump face left
	pAni = new Animation(100);
	pAni->Add(11402, 5);
	am->Add(FIRE_MARIO_STATE_AIR_LEFT, pAni);

	//normal jump face right
	pAni = new Animation(100);
	pAni->Add(11414, 5);
	am->Add(FIRE_MARIO_STATE_AIR_RIGHT, pAni);

	//p speed face left
	pAni = new Animation(100);
	pAni->Add(11102, 5);
	pAni->Add(11103, 5);
	pAni->Add(11104, 5);
	am->Add(FIRE_MARIO_STATE_RUN_LEFT, pAni);
	//p speed face right
	pAni = new Animation(100);
	pAni->Add(11113, 3);
	pAni->Add(11112, 3);
	pAni->Add(11114, 3);
	am->Add(FIRE_MARIO_STATE_RUN_RIGHT, pAni);
	//break left
	pAni = new Animation(100);
	pAni->Add(11115, 3);
	am->Add(FIRE_MARIO_STATE_BRAKE_LEFT, pAni);
	//break right
	pAni = new Animation(100);
	pAni->Add(11101, 3);
	am->Add(FIRE_MARIO_STATE_BRAKE_RIGHT, pAni);
	
}
void LoadedResources::createTanukiMarioAnimation()
{
	AnimationManage* am = AnimationManage::getInstance();
	Animation* pAni;
	//idle face left
	pAni = new Animation(100);
	pAni->Add(11707, 5);
	am->Add(TANUKI_MARIO_STATE_IDLE_LEFT, pAni);
	//idle face right
	pAni = new Animation(100);
	pAni->Add(11709, 5);
	am->Add(TANUKI_MARIO_STATE_IDLE_RIGHT, pAni);

	//walk face left
	pAni = new Animation(100);
	pAni->Add(11705, 5);
	pAni->Add(11707, 5);
	am->Add(TANUKI_MARIO_STATE_WALK_LEFT, pAni);

	//walk face right
	pAni = new Animation(100);
	pAni->Add(11711, 5);
	pAni->Add(11709, 5);
	am->Add(TANUKI_MARIO_STATE_WALK_RIGHT, pAni);

	//normal jump face left
	pAni = new Animation(100);
	pAni->Add(12002, 5);
	am->Add(TANUKI_MARIO_STATE_AIR_LEFT, pAni);

	//normal jump face right
	pAni = new Animation(100);
	pAni->Add(12014, 5);
	am->Add(TANUKI_MARIO_STATE_AIR_RIGHT, pAni);

	//p speed face left
	pAni = new Animation(100);
	pAni->Add(11702, 5);
	pAni->Add(11703, 5);
	pAni->Add(11704, 5);
	am->Add(TANUKI_MARIO_STATE_RUN_LEFT, pAni);
	//p speed face right
	pAni = new Animation(100);
	pAni->Add(11713, 3);
	pAni->Add(11712, 3);
	pAni->Add(11714, 3);
	am->Add(TANUKI_MARIO_STATE_RUN_RIGHT, pAni);
	//break left
	pAni = new Animation(100);
	pAni->Add(11715, 3);
	am->Add(TANUKI_MARIO_STATE_BRAKE_LEFT, pAni);
	//break right
	pAni = new Animation(100);
	pAni->Add(11701, 3);
	am->Add(TANUKI_MARIO_STATE_BRAKE_RIGHT, pAni);
}
void LoadedResources::createSmallMarioAnimation()
{
	AnimationManage* am = AnimationManage::getInstance();
	Animation* pAni;
	//idle face left
	pAni = new Animation(100);
	pAni->Add(10107, 5);
	am->Add(100, pAni);
	//idle face right
	pAni = new Animation(100);
	pAni->Add(10109, 5);
	am->Add(101, pAni);

	//walk face left
	pAni = new Animation(100);
	pAni->Add(10105, 5);
	pAni->Add(10107, 5);
	am->Add(102, pAni);

	//walk face right
	pAni = new Animation(100);
	pAni->Add(10111, 5);
	pAni->Add(10109, 5);
	am->Add(103, pAni);

	//normal jump face left
	pAni = new Animation(100);
	pAni->Add(10302, 5);
	am->Add(104, pAni);

	//normal jump face right
	pAni = new Animation(100);
	pAni->Add(10314, 5);
	am->Add(105, pAni);

	//p speed face left
	pAni = new Animation(100);
	pAni->Add(10301, 5);
	pAni->Add(10106, 5);
	am->Add(106, pAni);
	//p speed face right
	pAni = new Animation(100);
	pAni->Add(10110, 3);
	pAni->Add(10315, 3);
	am->Add(107, pAni);
	//break left
	pAni = new Animation(100);
	pAni->Add(10115, 3);
	am->Add(108, pAni);
	//break right
	pAni = new Animation(100);
	pAni->Add(10101, 3);
	am->Add(109, pAni);
}
void LoadedResources::createBigMarioAnimation()
{
	AnimationManage* am = AnimationManage::getInstance();
	Animation* pAni;
	//idle face left
	pAni = new Animation(100);
	pAni->Add(10507, 5);
	am->Add(BIG_MARIO_STATE_IDLE_LEFT, pAni);
	//idle face right
	pAni = new Animation(100);
	pAni->Add(10509, 5);
	am->Add(BIG_MARIO_STATE_IDLE_RIGHT, pAni);

	//walk face left
	pAni = new Animation(100);
	pAni->Add(10505, 5);
	pAni->Add(10507, 5);
	am->Add(BIG_MARIO_STATE_WALK_LEFT, pAni);

	//walk face right
	pAni = new Animation(100);
	pAni->Add(10511, 5);
	pAni->Add(10509, 5);
	am->Add(BIG_MARIO_STATE_WALK_RIGHT, pAni);

	//normal jump face left
	pAni = new Animation(100);
	pAni->Add(10802, 5);
	am->Add(BIG_MARIO_STATE_AIR_LEFT, pAni);

	//normal jump face right
	pAni = new Animation(100);
	pAni->Add(10814, 5);
	am->Add(BIG_MARIO_STATE_AIR_RIGHT, pAni);

	//p speed face left
	pAni = new Animation(100);
	pAni->Add(10502, 5);
	pAni->Add(10503, 5);
	pAni->Add(10504, 5);
	am->Add(BIG_MARIO_STATE_RUN_LEFT, pAni);
	//p speed face right
	pAni = new Animation(100);
	pAni->Add(10513, 3);
	pAni->Add(10512, 3);
	pAni->Add(10514, 3);
	am->Add(BIG_MARIO_STATE_RUN_RIGHT, pAni);
	//break left
	pAni = new Animation(100);
	pAni->Add(10515, 3);
	am->Add(BIG_MARIO_STATE_BRAKE_LEFT, pAni);
	//break right
	pAni = new Animation(100);
	pAni->Add(10501, 3);
	am->Add(BIG_MARIO_STATE_BRAKE_RIGHT, pAni);
}
LoadedResources* LoadedResources::getInstance()
{
	if (__instance == NULL) __instance = new LoadedResources();
	return __instance;
}

void LoadedResources::LoadResources()
{
	
	TextureManager* tm = TextureManager::getInstance();
	AnimationManage* am = AnimationManage::getInstance();
	SpriteManage* sm = SpriteManage::getInstance();

	Animation* pAni;
	//idle animation;
	tm->Add(0, MARIO_TEX);
	tm->Add(1, ENEMY_TEX);
	tm->Add(2, MISC_TEX);
	tm->Add(3, TILE_TEX);
	loadMarioSprite();
	// misc sprite.
	//golden brick
	sm->Add(2101, 300, 135, 315, 150, tm->getTextureWithId(2));
	sm->Add(2102, 318, 135, 333, 150, tm->getTextureWithId(2));
	sm->Add(2103, 336, 135, 351, 150, tm->getTextureWithId(2));
	sm->Add(2104, 354, 135, 369, 150, tm->getTextureWithId(2));
	sm->Add(2105, 372, 135, 387, 150, tm->getTextureWithId(2));

	//goomba sprite
	sm->Add(4101, 5, 14, 21, 30, tm->getTextureWithId(1));
	sm->Add(4102, 25, 14, 41, 30, tm->getTextureWithId(1));
	sm->Add(4103, 45, 14, 61, 30, tm->getTextureWithId(1));
	//red kooba sprite
	sm->Add(4401, 6, 128, 22, 156, tm->getTextureWithId(1),0.0f,-30.0f);
	sm->Add(4402, 27, 128, 43, 156, tm->getTextureWithId(1), 0.0f, -30.0f);
	sm->Add(4403, 49, 128, 65, 156, tm->getTextureWithId(1), 0.0f, -30.0f);
	sm->Add(4404, 71, 128, 88, 156, tm->getTextureWithId(1), 0.0f, -30.0f);
	Animation* goomBaWallkAnimation = new Animation(100);
	goomBaWallkAnimation->Add(4101,3);
	goomBaWallkAnimation->Add(4102, 3);
	am->Add(4001, goomBaWallkAnimation);
	goomBaWallkAnimation = new Animation(100);
	goomBaWallkAnimation->Add(4103, 3);
	am->Add(4009, goomBaWallkAnimation);
	Animation* RedKoobaAni = new Animation(100);
	RedKoobaAni->Add(4401, 3);
	RedKoobaAni->Add(4402, 3);
	am->Add(4101, RedKoobaAni);
	RedKoobaAni = new Animation(100);
	RedKoobaAni->Add(4403, 3);
	am->Add(4109, RedKoobaAni);


	//red mushroom
	sm->Add(2201, 300, 190, 315, 205, tm->getTextureWithId(2));
	//leaf
	sm->Add(2202, 300, 208, 315, 222, tm->getTextureWithId(2));
	Animation* MushroomAni = new Animation(100);
	MushroomAni->Add(2201, 3);
	//MushroomAni->Add(2102, 3);
	am->Add(4201, MushroomAni);
	//leaf animation;
    MushroomAni = new Animation(100);
	MushroomAni->Add(2202, 3);
	//MushroomAni->Add(2102, 3);
	am->Add(4202, MushroomAni);
	
	//red plant
	Animation* PlantsAni = new Animation(100);
	sm->Add(4501, 151,64 ,166, 85, tm->getTextureWithId(1));
	sm->Add(4502, 197, 64, 212, 85, tm->getTextureWithId(1));
	PlantsAni->Add(4501, 3);
	PlantsAni->Add(4502, 3);
	am->Add(4301,PlantsAni);


	//green plant
	PlantsAni = new Animation(100);
	sm->Add(4503, 241, 64, 256, 85, tm->getTextureWithId(1));
	PlantsAni->Add(4503, 3);
	am->Add(4302, PlantsAni);

	//green fire plant
	PlantsAni = new Animation(100);
	sm->Add(4504, 106, 64, 121, 85, tm->getTextureWithId(1));
	PlantsAni->Add(4504, 3);
	am->Add(4303, PlantsAni);

	//red fire plant
	PlantsAni = new Animation(100);
	sm->Add(4505, 60, 64, 75, 85, tm->getTextureWithId(1));
	sm->Add(4506, 106, 64, 13, 85, tm->getTextureWithId(1));
	PlantsAni->Add(4505, 3);
	PlantsAni->Add(4506, 3);
	am->Add(4304, PlantsAni);
	// tile
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			int _top = 2*(i+1) + (i * 16);
			int _left = 2 * (j + 1) + (j * 16);
			int _right = _left + 16;
			int _bottom = _top + 16;
			sm->Add(30000 + (i+1) * 100 + (j+1),  _left, _top, _right, _bottom,tm->getTextureWithId(3));
		}
	}
	createMarioAnimation();
	
	// create brick animation;
	Animation* pBrickAnimation = new Animation(100);
	pBrickAnimation->Add(2101, 3);
	pBrickAnimation->Add(2102, 3);
	pBrickAnimation->Add(2103, 3);
	pBrickAnimation->Add(2104, 3);
	pBrickAnimation->Add(2105, 3);
	am->Add(2001, pBrickAnimation);
	

	//create question block animation;
	Animation* questionBlockAni = new Animation(100);
	questionBlockAni->Add(30611, 7);
	questionBlockAni->Add(30612, 3);
	questionBlockAni->Add(30613, 3);
	questionBlockAni->Add(30614, 3);
	am->Add(3001, questionBlockAni);
	//create disabled block ani
	Animation* DisableBlockAni = new Animation(100);
	DisableBlockAni->Add(30815, 7);
	am->Add(3099, DisableBlockAni);


	
	Mario = new PlayableCharacter(15.0f,600.0f);
	/*Mario->AddAnimation(100);
	Mario->AddAnimation(101);
	Mario->AddAnimation(102);
	Mario->AddAnimation(103);
	Mario->AddAnimation(104);
	Mario->AddAnimation(105);
	Mario->AddAnimation(106);
	Mario->AddAnimation(107);*/
	stage_blocks.push_back(new WoodenFloor(BRICK_WIDTH*SCALE_WIDTH/2.0f,(BRICK_HEIGHT*SCALE_HEIGHT)/2.0f , 39, 2));
	stage_blocks.push_back(new WoodenFloor((BRICK_WIDTH * SCALE_WIDTH / 2.0f)+39* BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f, 29, 3));
	stage_blocks.push_back(new QuestionBlock((BRICK_WIDTH * SCALE_WIDTH / 2.0f)  + 11* BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 5*BRICK_HEIGHT*SCALE_HEIGHT));
	stage_blocks.push_back(new QuestionBlock((BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 12 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 5 * BRICK_HEIGHT * SCALE_HEIGHT));
	
	stage_blocks.push_back(new QuestionBlock((BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 14 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 7 * BRICK_HEIGHT * SCALE_HEIGHT));
	stage_blocks.push_back(new QuestionBlock((BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 15 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 7 * BRICK_HEIGHT * SCALE_HEIGHT, true));


	stage_blocks.push_back(new Pipe(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 21 * BRICK_WIDTH * SCALE_WIDTH, //x
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,//y
		1,
		3));
	stage_blocks.push_back(new Box(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 17 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,
		3, 5, 2));
	stage_blocks.push_back(new Box(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 15 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,
		3,3,1));

	stage_blocks.push_back(new Box(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 31 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,
		5, 7, 4));
	stage_blocks.push_back(new Box(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 28 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,
		4, 5, 1));
	stage_blocks.push_back(new Box(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 24 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,
		5, 3, 3));
	stage_blocks.push_back(new Box(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 31 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT,
		7, 2, 3));
	/*stage_blocks.push_back(new QuestionBlock(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 40 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 2 * BRICK_HEIGHT * SCALE_HEIGHT
		));*/
	stage_blocks.push_back(new QuestionBlock(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 41 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 3 * BRICK_HEIGHT * SCALE_HEIGHT,
		true
	));
	stage_blocks.push_back(new QuestionBlock(
		(BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 44 * BRICK_WIDTH * SCALE_WIDTH,
		(BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f + 5 * BRICK_HEIGHT * SCALE_HEIGHT
	));
	stage_blocks.push_back(new WoodenFloor((BRICK_WIDTH * SCALE_WIDTH / 2.0f) + 70 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT * SCALE_HEIGHT) / 2.0f, 23, 2));
	/*for (int i = 0; i < 20; i++){
		stage_blocks.push_back(new Platform(SCALE_WIDTH*BRICK_WIDTH*(i)+20.0f, SCALE_HEIGHT*BRICK_HEIGHT/2));
		stage_blocks[i]->AddAnimation(2001);
	}
	for (int i = 0; i < 20; i++) {
		stage_blocks.push_back(new Platform(200.0f, SCALE_HEIGHT * BRICK_HEIGHT *(i)+20.0f));
		stage_blocks[i+20]->AddAnimation(2001);
	}*/
	enemies.push_back(new Goomba((BRICK_WIDTH* SCALE_WIDTH / 2.0f) + 12 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT* SCALE_HEIGHT) / 2.0f + 2* BRICK_HEIGHT * SCALE_HEIGHT));
	
	enemies.push_back(new RedKooba((BRICK_WIDTH* SCALE_WIDTH / 2.0f) + 34 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT* SCALE_HEIGHT) / 2.0f + 4.1f * BRICK_HEIGHT * SCALE_HEIGHT));
	enemies.push_back(new Mushroom((BRICK_WIDTH* SCALE_WIDTH / 2.0f) + 15 * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT* SCALE_HEIGHT) / 2.0f + 9 * BRICK_HEIGHT * SCALE_HEIGHT));
	enemies.push_back(new Plant((BRICK_WIDTH* SCALE_WIDTH / 2.0f) + 21.5f * BRICK_WIDTH * SCALE_WIDTH, (BRICK_HEIGHT* SCALE_HEIGHT) / 2.0f + 5 * BRICK_HEIGHT * SCALE_HEIGHT));

}

void LoadedResources::Update(DWORD dt)
{
	//
	playableCollision = false;
	int e_l = enemies.size();
	for (auto it = enemies.begin(); it != enemies.end() && enemies.size() > 0; it++) {
		if ((*it)->is_delete) {
			auto p_it = it;
			if (it != enemies.begin())
				p_it--;
			GameObject* t = (* it);
			delete t;
			enemies.erase(it);
			if (enemies.size() == 0)
				break;
			if (it != enemies.begin())
				it = p_it;
			continue;
		}
		(*it)->Update(dt);
	}
	for (int i = 0; i < stage_blocks.size(); i++) {
		stage_blocks[i]->Update(dt);
	}
	for (int i = 0; i < Attack.size(); i++) {
		Attack[i]->Update(dt);
	}
	Mario->Update(dt);

	checCollisionMarioToStageBlocks(dt);
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i])
			checkCollisionEnemiesToStageBlocks(dt,enemies[i]);
	}
	checCollisionMarioToEnemies(dt);
	std::vector<int> deleted_index;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->is_delete) {
			deleted_index.push_back(i);
		}
	}
	for (int i = 0; i < deleted_index.size(); i++) {
		auto it = enemies.begin();
		int c = 0;
		while (c < deleted_index[i]) {
			c += 1;
			it++;
		}
		enemies.erase(it);
	}
}
void LoadedResources::checCollisionMarioToEnemies(DWORD dt) {

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
		Scan(Mario, dt, &enemies, collisionEvents);
	}
	//no colision
	if (collisionEvents.size() == 0) {
		if (playableCollision) {

		}
		else {
			Mario->OnNoCollision();
			playableCollision = true;
		}
	}
	else {
		//get who have collision first in X axis and Y axis
		Filter(Mario, collisionEvents, colX, colY,0,1,1);

		float x, y, vx, vy, dx, dy;
		Mario->GetPosition(x, y);
		Mario->GetSpeed(vx, vy);
		dx = vx;
	    dy = vy;

		if (colX != NULL && colY != NULL)
		{
			if (colY->t < colX->t)	// was collision on Y first ?
			{
				Mario->onCollisionWithEnemy(colY);

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

					if (colX_other->t < 0) {
					}
					else {
						x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
						SweptAABB(Mario, dt, colX_other->des);
						Mario->onCollisionWithEnemy(colX_other);
					}

				}
				else
				{
					x += dx;
				}
			}
			else // collision on X first
			{
				//x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				SweptAABB(Mario, dt, colX->des);
				Mario->onCollisionWithEnemy(colX);

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
					//y += colY_other->t * dy + colY_other->ny * BLOCK_PUSH_FACTOR;
					Mario->onCollisionWithEnemy(colY_other);
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
				//x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				y += dy;
				Mario->onCollisionWithEnemy(colX);
			}
			else
				if (colY != NULL)
				{
					x += dx;
					//y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
					Mario->onCollisionWithEnemy(colY);
				}
				else // both colX & colY are NULL 
				{
					x += dx;
					y += dy;
				}

		//Mario->SetPosition(x, y);
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
void LoadedResources::checCollisionMarioToStageBlocks(DWORD dt) {

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
		if (playableCollision) {

		}
		else {
			Mario->OnNoCollision();
			playableCollision = true;
		}
	}
	else {
		//get who have collision first in X axis and Y axis

		Filter(Mario, collisionEvents, colX, colY);

		float x, y, vx, vy, dx, dy;
		Mario->GetPosition(x, y);
		Mario->GetSpeed(vx, vy);
		dx = vx;
		dy = vy;

		if (colX != NULL && colY != NULL)
		{
			if (colY->t < colX->t)	// was collision on Y first ?
			{
				//y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
				//Mario->SetPosition(x, y);

				Mario->onCollisionWith(colY,true);

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

					if (colX_other->t < 0) {
					}
					else {
						//x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
						SweptAABB(Mario, dt, colX_other->des);
						Mario->onCollisionWith(colX_other,false);
					}

				}
				else
				{
					x += dx;
				}
			}
			else // collision on X first
			{
				//x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				SweptAABB(Mario, dt, colX->des);
				//Mario->SetPosition(x, y);

				Mario->onCollisionWith(colX,true);

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
					//y += colY_other->t * dy + colY_other->ny * BLOCK_PUSH_FACTOR;
					Mario->onCollisionWith(colY_other,false);
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
				/*x += colX->t * dx + colX->nx * BLOCK_PUSH_FACTOR;
				y += dy;*/
				Mario->onCollisionWith(colX,false);
			}
			else
				if (colY != NULL)
				{
					/*x += dx;
					y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;*/
					Mario->onCollisionWith(colY,false);
				}
				else // both colX & colY are NULL 
				{
					x += dx;
					y += dy;
					Mario->SetPosition(x, y);
				}

	
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

void LoadedResources::checkCollisionEnemiesToStageBlocks(DWORD dt, GameObject* enemy)
{
	//world stuff
	// -  collsion check between varies gameobjects.
	// - moving gameobject according to their speed.
	
	std::vector<CollisionEvent* > collisionEvents;
	//std::vector<CollisionEvent*> &coEvents
	CollisionEvent* colX = NULL;
	CollisionEvent* colY = NULL;
	collisionEvents.clear();
	// check for everything 
	
	if (enemy->isCollidable()) {
		Scan(enemy, dt, &stage_blocks, collisionEvents);
	}
	//no colision
	
	if (collisionEvents.size() == 0) {
		enemy->OnNoCollision();
	}
	else {
		//get who have collision first in X axis and Y axis
		GameObject* enemies = enemy;
		Filter(enemies, collisionEvents, colX, colY);

		float x, y, vx, vy, dx, dy;
		enemies->GetPosition(x, y);
		enemies->GetSpeed(vx, vy);
		dx = vx;
		dy = vy;

		if (colX != NULL && colY != NULL)
		{
			if (colY->t < colX->t)	// was collision on Y first ?
			{
				//y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
				//enemies->SetPosition(x, y);

				enemies->onCollisionWith(colY,true);

				//
				// see if after correction on Y, is there still a collision on X ? 
				//
				CollisionEvent* colX_other = NULL;

				//
				// check again if there is true collision on X 
				//
				colX->isDeleted = true;		// remove current collision event on X

				// replace with a new collision event using corrected location 
				collisionEvents.push_back(SweptAABB(enemies, dt, colX->des));

				// re-filter on X only
				Filter(enemies, collisionEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);

				if (colX_other != NULL)
				{

					if (colX_other->t < 0) {
					}
					else {
					//	x += colX_other->t * dx + colX_other->nx * BLOCK_PUSH_FACTOR;
						if (dynamic_cast<RedKooba*>(enemy)) {
							dynamic_cast<RedKooba*>(enemy);
						}
						enemies->onCollisionWith(colX_other,false);
						x = x;
					}

				}
				else
				{
					x += dx;
				}
			}
			else // collision on X first
			{
				
				//enemies->SetPosition(x, y);
				enemies->onCollisionWith(colX,true);

				//
				// see if after correction on X, is there still a collision on Y ? 
				//
				CollisionEvent* colY_other = NULL;

				//
				// check again if there is true collision on Y
				//
				colY->isDeleted = true;		// remove current collision event on Y

				// replace with a new collision event using corrected location 
				collisionEvents.push_back(SweptAABB(enemies, dt, colY->des));

				// re-filter on Y only
				Filter(enemies, collisionEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);

				if (colY_other != NULL)
				{
				//	y += colY_other->t * dy + colY_other->ny * BLOCK_PUSH_FACTOR;
					enemies->onCollisionWith(colY_other,false);
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
				if (dynamic_cast<RedKooba*>(enemy)) {
					dynamic_cast<RedKooba*>(enemy);
				}
				enemies->onCollisionWith(colX,false);
			}
			else
				if (colY != NULL)
				{
					x += dx;
					y += colY->t * dy + colY->ny * BLOCK_PUSH_FACTOR;
					if (dynamic_cast<RedKooba*>(enemy)) {
						dynamic_cast<RedKooba*>(enemy);
					}
					enemies->onCollisionWith(colY,false);
				}
				else // both colX & colY are NULL 
				{
					x += dx;
					y += dy;
				}

		//enemies->SetPosition(x, y);
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
