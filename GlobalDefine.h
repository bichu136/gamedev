#pragma once


//windows info
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

//background color
#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)


//frame rate
#define MAX_FRAME_RATE 60


//Resource files
#define TEXTURE_DIR L"assets"

#define MARIO_TEX TEXTURE_DIR "\\mario.png"
#define ENEMY_TEX TEXTURE_DIR "\\enemies.png"
#define MISC_TEX TEXTURE_DIR "\\misc.png"
#define TILE_TEX TEXTURE_DIR "\\tiles_trans.png"


#define LEFT  0
#define RIGHT 1
#define ASUNASPRITE214_BASE 
#define MARIO_STATE_DIE -1
#define MARIO_STATE_IDLE_LEFT  100
#define MARIO_STATE_IDLE_RIGHT 101
#define MARIO_STATE_WALK_LEFT  102
#define MARIO_STATE_WALK_RIGHT 103
#define MARIO_STATE_RUN_LEFT   106
#define MARIO_STATE_RUN_RIGHT  107
#define MARIO_STATE_AIR   1040
#define MARIO_STATE_AIR_LEFT   104
#define MARIO_STATE_AIR_RIGHT  105
#define MARIO_STATE_BRAKE_LEFT   108
#define MARIO_STATE_BRAKE_RIGHT  109


#define MARIO_WIDTH 25
#define MARIO_HEIGHT 20

#define BRICK_WIDTH 16
#define BRICK_HEIGHT 16
