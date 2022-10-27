#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "GameObject.h"

#define SCREEN_X 32
#define SCREEN_Y 16

//Posicio inicial persona
#define INIT_PLAYER_X_TILES 12
#define INIT_PLAYER_Y_TILES 16

#define INIT_ENEMY_X_TILES 24
#define INIT_ENEMY_Y_TILES 16



Scene::Scene()
{
	map = NULL;
	//objects = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (objects.size() > 0) {
		for (int i = 0; i < objects.size(); ++i) {
			delete objects[i];
		}
	}
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	//Player
	GameObject *mainPlayer = GameObject::make_Object(0);
	mainPlayer->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	mainPlayer->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	mainPlayer->setTileMap(map);
	objects.push_back(mainPlayer);
	 
	////Enemy
	GameObject *enemigo = GameObject::make_Object(1);
	enemigo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemigo->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemigo->setTileMap(map);
	objects.push_back(enemigo);
			
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->update(deltaTime);
	}
}

void Scene::render()
{
	map->render();
	float velocity = currentTime / 20;
	projection = glm::ortho(0.f + velocity, float(SCREEN_WIDTH - 1 + velocity), float(SCREEN_HEIGHT - 1), 0.f);

	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->render();
	}

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



