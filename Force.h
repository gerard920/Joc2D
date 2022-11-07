#ifndef _FORCE_INCLUDE
#define _FORCE_INCLUDE


#include "GameObject.h"


class Force : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

	int getType();

	bool detectColisionMap(glm::ivec2 posAnterior);


};

#endif // _FORCE_INCLUDE