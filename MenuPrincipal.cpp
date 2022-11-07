#include "MenuPrincipal.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glut.h>


#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

MenuPrincipal::MenuPrincipal() {
	sprite = NULL;
	background = NULL;
	
}	

MenuPrincipal::~MenuPrincipal() {
	if (sprite != NULL) delete sprite;
	if (background != NULL) delete background;
}

void MenuPrincipal::init(const int& idScene) {

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();

	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	background = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	//Load textures
	sceneMenu.loadFromFile("images/WinGame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sceneCredits.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGB);
	sceneIns.loadFromFile("images/Instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sceneWin.loadFromFile("images/WinGame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sceneLoose.loadFromFile("images/Loose.png", TEXTURE_PIXEL_FORMAT_RGBA);

	Game::instance().setStatusGame(0);
}

void MenuPrincipal::update(int deltaTime, int id) {
	currentTime += deltaTime;

	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	idScene = id;	
}


void MenuPrincipal::render() {	
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	currentTime = 0.0f;	

	switch (idScene) {
	case 0:
		background->render(sceneMenu);
		break;
	case 1:
		background->render(sceneCredits);
		break;
	case 2:
		background->render(sceneIns);
		break;
	
	case 3:
		background->render(sceneLoose);
		break;
	
	case 4:
		background->render(sceneWin);
		break;
	}
}

void MenuPrincipal::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if (!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
}

int MenuPrincipal::getIdScene(){
	return idScene;
}

