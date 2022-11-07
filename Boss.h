#include "GameObject.h"


class Boss : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	int getType();

};