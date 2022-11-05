#include "GameObject.h"


class Enemy1 : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

	bool subiendo, bajando;
	bool detectColisionMap(glm::ivec2 posAnterior);
	int getType();
	virtual vector<GameObject*> disparar(ShaderProgram texProgram);

};