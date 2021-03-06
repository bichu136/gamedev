#pragma once


//windows info
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

//background color
#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCALE_WIDTH 3.0f
#define SCALE_HEIGHT 3.0f

//frame rate
#define MAX_FRAME_RATE 60

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

//Resource files
#define TEXTURE_DIR L"assets"

#define MARIO_TEX TEXTURE_DIR "\\mario.png"
#define ENEMY_TEX TEXTURE_DIR "\\enemies.png"
#define MISC_TEX TEXTURE_DIR "\\misc.png"
#define TILE_TEX TEXTURE_DIR "\\tiles_trans1.png"

#define LEFT  0
#define RIGHT 1
#define ASUNASPRITE214_BASE 
#define MARIO_STATE_DIE -1
#define SMALL_MARIO_STATE_IDLE_LEFT  100
#define SMALL_MARIO_STATE_IDLE_RIGHT 101
#define SMALL_MARIO_STATE_WALK_LEFT  102
#define SMALL_MARIO_STATE_WALK_RIGHT 103
#define SMALL_MARIO_STATE_RUN_LEFT   106
#define SMALL_MARIO_STATE_RUN_RIGHT  107
#define SMALL_MARIO_STATE_AIR   1040
#define SMALL_MARIO_STATE_AIR_LEFT   104
#define SMALL_MARIO_STATE_AIR_RIGHT  105
#define SMALL_MARIO_STATE_BRAKE_LEFT   108
#define SMALL_MARIO_STATE_BRAKE_RIGHT  109

#define BIG_MARIO_STATE_IDLE_LEFT  200
#define BIG_MARIO_STATE_IDLE_RIGHT 201
#define BIG_MARIO_STATE_WALK_LEFT  202
#define BIG_MARIO_STATE_WALK_RIGHT 203
#define BIG_MARIO_STATE_RUN_LEFT   206
#define BIG_MARIO_STATE_RUN_RIGHT  207
#define BIG_MARIO_STATE_AIR   2040
#define BIG_MARIO_STATE_AIR_LEFT   204
#define BIG_MARIO_STATE_AIR_RIGHT  205
#define BIG_MARIO_STATE_BRAKE_LEFT   208
#define BIG_MARIO_STATE_BRAKE_RIGHT  209

#define FIRE_MARIO_STATE_IDLE_LEFT  300
#define FIRE_MARIO_STATE_IDLE_RIGHT 301
#define FIRE_MARIO_STATE_WALK_LEFT  302
#define FIRE_MARIO_STATE_WALK_RIGHT 303
#define FIRE_MARIO_STATE_RUN_LEFT   306
#define FIRE_MARIO_STATE_RUN_RIGHT  307
#define FIRE_MARIO_STATE_AIR   2040
#define FIRE_MARIO_STATE_AIR_LEFT   304
#define FIRE_MARIO_STATE_AIR_RIGHT  305
#define FIRE_MARIO_STATE_BRAKE_LEFT   308
#define FIRE_MARIO_STATE_BRAKE_RIGHT  309

#define TANUKI_MARIO_STATE_IDLE_LEFT  400
#define TANUKI_MARIO_STATE_IDLE_RIGHT 401
#define TANUKI_MARIO_STATE_WALK_LEFT  402
#define TANUKI_MARIO_STATE_WALK_RIGHT 403
#define TANUKI_MARIO_STATE_RUN_LEFT   406
#define TANUKI_MARIO_STATE_RUN_RIGHT  407
#define TANUKI_MARIO_STATE_AIR   2040
#define TANUKI_MARIO_STATE_AIR_LEFT   404
#define TANUKI_MARIO_STATE_AIR_RIGHT  405
#define TANUKI_MARIO_STATE_BRAKE_LEFT   408
#define TANUKI_MARIO_STATE_BRAKE_RIGHT  409


#define SMALL 0
#define BIG 1
#define FIRE 3
#define TANUKI 2

#define SMALL_MARIO_WIDTH 15.0f
#define SMALL_MARIO_HEIGHT 15.0f
#define BIG_MARIO_WIDTH 15.0f
#define BIG_MARIO_HEIGHT 30.0f
#define BRICK_WIDTH 16.0f
#define BRICK_HEIGHT 16.0f

#define WOODEN_FLOOR_SPRITE_8 30718
#define WOODEN_FLOOR_SPRITE_4 30817
#define WOODEN_FLOOR_SPRITE_2 -1
#define WOODEN_FLOOR_SPRITE_6 30819
#define WOODEN_FLOOR_SPRITE_7 30717
#define WOODEN_FLOOR_SPRITE_9 30719
#define WOODEN_FLOOR_SPRITE_1 -1
#define WOODEN_FLOOR_SPRITE_3 -1
#define WOODEN_FLOOR_SPRITE_5 30818

#define BOX_1_SPRITE_8 30118
#define BOX_1_SPRITE_4 30217
#define BOX_1_SPRITE_2 30318
#define BOX_1_SPRITE_6 30219
#define BOX_1_SPRITE_7 30117
#define BOX_1_SPRITE_9 30119
#define BOX_1_SPRITE_1 30317
#define BOX_1_SPRITE_3 30319
#define BOX_1_SPRITE_5 30218


#define BOX_2_SPRITE_8 30121+1
#define BOX_2_SPRITE_4 30220+1
#define BOX_2_SPRITE_2 30321+1
#define BOX_2_SPRITE_6 30222+1
#define BOX_2_SPRITE_7 30120+1
#define BOX_2_SPRITE_9 30122+1
#define BOX_2_SPRITE_1 30320+1
#define BOX_2_SPRITE_3 30322+1
#define BOX_2_SPRITE_5 30221+1


#define BOX_3_SPRITE_8 30418
#define BOX_3_SPRITE_4 30517
#define BOX_3_SPRITE_2 30618
#define BOX_3_SPRITE_6 30519
#define BOX_3_SPRITE_7 30417
#define BOX_3_SPRITE_9 30419
#define BOX_3_SPRITE_1 30617
#define BOX_3_SPRITE_3 30619
#define BOX_3_SPRITE_5 30518

#define BOX_4_SPRITE_8 30422
#define BOX_4_SPRITE_4 30521
#define BOX_4_SPRITE_2 30622
#define BOX_4_SPRITE_6 30523
#define BOX_4_SPRITE_7 30421
#define BOX_4_SPRITE_9 30423
#define BOX_4_SPRITE_1 30621
#define BOX_4_SPRITE_3 30623
#define BOX_4_SPRITE_5 30522
