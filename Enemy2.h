#include "GameObject.h"


class Enemy2 : public GameObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();


	bool subiendo, bajando;
	bool detectColisionMap(glm::ivec2 posAnterior);
	int getType();
	int currentTime;
	int rad;
	glm::ivec2 initialPosition;

};