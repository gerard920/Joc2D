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
	virtual void update(int deltaTime, const glm::vec2 &mainPlayerPos);
	virtual void render();

	virtual void setTileMap(TileMap *tileMap);
	virtual glm::ivec2 getPosition();
	virtual void setPosition(const glm::vec2 &pos);
	virtual int getType();
	virtual bool isAlive();
	virtual void setAlive(bool alive);
	virtual void setSizePlayer(const glm::vec2 &size);
	virtual glm::ivec2 getSizePlayer();
	virtual glm::ivec2 getMainPlayerPos();

	virtual void setLives(int lives);

	virtual void setInvulnerable(bool invulnerable);
	virtual bool getInvulnerable();

	virtual void setSubtype(int subtype);
	virtual int getSubtype();

	virtual bool detectColisionMap(glm::ivec2 posAnterior);
	virtual bool detectColisionObject(vector<GameObject*> objects, int index);

	bool collisionMoveLeft(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const;
	bool collisionMoveRight(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const;
	bool collisionMoveUp(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const;
	bool collisionMoveDown(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const;

	virtual void quitarVida();


	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;


	enum GameObjectAnims {
		STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,
		STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN
	};

	virtual vector<GameObject*> disparar(ShaderProgram texProgram);
	


private:
	glm::ivec2 tileMapDispl, posPlayer, sizePlayer, mainPlayerPos;
	bool alive, invulnerable;
	int lives, type, subtype;
	bool canColision(int objectX, int objectY);
	


};

#endif // _GAMEOBJECT_INCLUDE