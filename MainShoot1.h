#ifndef _MAINSHOOT1_INCLUDE
#define _MAINSHOOT1_INCLUDE


#include "GameObject.h"


class MainShoot1 : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

	int getType();

};

#endif // _MAINSHOOT1_INCLUDE