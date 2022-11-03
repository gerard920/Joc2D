#ifndef _EnemyShoot1_INCLUDE
#define _EnemyShoot1_INCLUDE


#include "GameObject.h"


class EnemyShoot1 : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

	int getType();

	bool detectColisionMap(glm::ivec2 posAnterior);


};

#endif // _EnemyShoot1_INCLUDE