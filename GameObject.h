#ifndef _GAMEOBJECT_INCLUDE
#define _GAMEOBJECT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class GameObject
{
public:
	static GameObject *make_Object(int typeObject);

	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();

	virtual void setTileMap(TileMap *tileMap);
	virtual glm::ivec2 getPosition();
	virtual void setPosition(const glm::vec2 &pos);
	virtual int getType();
	virtual bool isAlive();

	virtual bool detectColisionMap();
	virtual bool detectColisionObject(vector<GameObject*> objects, int index);

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	int coliderx, colidery, radius;

	enum GameObjectAnims {
		STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,
		STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN
	};

	


private:
	glm::ivec2 tileMapDispl, posPlayer;
	bool alive;
	int lives, type;

	bool canColision(int objectX, int objectY);

};

#endif // _GAMEOBJECT_INCLUDE