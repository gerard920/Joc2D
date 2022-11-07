#ifndef _EXPLOSION_INCLUDE
#define _EXPLOSION_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Explosion
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);

	void setTime(int time);
	int getTime();

private:
	int time;
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
};


#endif // _ENEMY_INCLUDE


