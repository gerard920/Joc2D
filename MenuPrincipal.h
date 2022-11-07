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
	void update(int deltaTime, int idScene);
	int getIdScene();

private: 
	void initShaders();


private:
	int idScene;
	Sprite* sprite;
	float currentTime;
	Texture spritesheetMenu;
	TexturedQuad* background;
	ShaderProgram simpleProgram, texProgram;
	glm::mat4 projection;
	Texture sceneMenu, sceneCredits, sceneIns, sceneWin, sceneLoose;
};

#endif // _MenuPrincipal_INCLUDE