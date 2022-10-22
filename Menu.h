#ifndef _MenuPrincipal_INCLUDE
#define _MenuPrincipal_INCLUDE

#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"

class MenuPrincipal {
public:
	MenuPrincipal();
	~MenuPrincipal();

	void init(const int& idScene);
	void render();
	void update(int deltaTime);
	void setPosIndex(int pos);

private:
	int id;
	Sprite* sprite;
	float currentTime;
	Texture spritesheet;
	TexturedQuad* bground;
	glm::mat4 projection;
	Texture scene, scene1, scene2;
};

#endif // _MenuPrincipal_INCLUDE