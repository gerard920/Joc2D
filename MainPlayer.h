#include "GameObject.h"


class MainPlayer : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

	int getType();
	bool detectColisionMap(glm::ivec2 posAnterior);

	void setInvulnerable(bool invulnerable, ShaderProgram &texProgram);


};