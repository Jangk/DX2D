#pragma once

enum DISPLAY_MODE
{
	MODE_FULL,
	MODE_WIN
};

enum TEXTURE_TYPE
{
	TEXTURE_SINGLE,
	TEXTURE_MULTI
};

enum OBJECT_TYPE
{
	OBJECT_TERRAIN,
	OBJECT_PLAYER,
	OBJECT_MONSTER,
	OBJECT_EFFECT,
	OBJECT_UI,
	OBJECT_BUTTON,
	OBJECT_CARD,
	OBJECT_END
};

enum SCENE_TYPE
{
	SCENE_LOGO,
	SCENE_CHARECTER_SELECTE,
	SCENE_WORLD_MAP,
	SCENE_STAGE,
	SCENE_END
};


enum PLAYER_STATE
{
	PLAYER_IDLE,
	PLAYER_HIT,
	PLAYER_DEAD,
};

enum PLAYABLE_CHARACTER
{
	CHARACTER_IRONCLAD,
	CHARACTER_SILENT,
	CHARACTER_DEFECT,
	CHARACTER_WATCHER,
	CHARACTER_END
};

enum WORLDMAP_TYPE
{
	WORLDMAP_TOP,
	WORLDMAP_MID,
	WORLDMAP_BOT,
	WORLDMAP_END
};

enum CARD_TYPE
{
	CARD_ATTACK,
	CARD_SKILL,
	CARD_POWER,
	CARD_TYPE_END
};