#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "GameObject.h"
#include "TexturedQuad.h"


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

	//fons negre
	//declarar el fons
	glm::vec2 geom1[2] = { glm::vec2(0.f, 0.f), glm::vec2(2250.f, 480.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fons = TexturedQuad::createTexturedQuad(geom1, texCoords2, texProgram);
	// Load textures
	tex1.loadFromFile("images/fonsnegre.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//declarar el fons
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(2250.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	// Load textures
	tex.loadFromFile("images/mapita.png", TEXTURE_PIXEL_FORMAT_RGBA);

	map = TileMap::createTileMap("levels/level011.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	//Player
	GameObject *mainPlayer = GameObject::make_Object(0);
	mainPlayer->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	mainPlayer->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	mainPlayer->setTileMap(map);
	objects.push_back(mainPlayer);
	posMainPlayer = mainPlayer->getPosition();

	 
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
	
	if (Game::instance().getKey(120) && (currentTime - lastShootPlayer)/1000 >= 1) {
		lastShootPlayer = currentTime;

		GameObject *shoot1 = GameObject::make_Object(2);
		shoot1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		shoot1->setPosition(glm::vec2((posMainPlayer.x + 86), posMainPlayer.y));
		shoot1->setTileMap(map);
		objects.push_back(shoot1);
	}

	for (int i = 0; i < objects.size(); ++i) {
		if (objects[i]->getType() == 0) {
			posMainPlayer = objects[i]->getPosition();
		}
		glm::ivec2 posAnterior = objects[i]->getPosition();
		objects[i]->update(deltaTime);
		objects[i]->detectColisionMap(posAnterior); 
		objects[i]->detectColisionObject(objects, i);
		if (!objects[i]->isAlive()) {
			deleteObject(i);
		}
	}

}

void Scene::render()
{
	fons->render(tex1);
	map->render();
	texQuad->render(tex);
	float velocity = currentTime / 200;
	projection = glm::ortho(0.f + velocity, float(SCREEN_WIDTH - 1 + velocity), float(SCREEN_HEIGHT - 1), 0.f);

	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->render();
	}



}

void Scene::deleteObject(int indexObject) {
	GameObject* eliminar = objects[indexObject];
	objects.erase(std::find(objects.begin(), objects.end(), objects[indexObject]));
	delete eliminar;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

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
	vShader.free();
	fShader.free();
}
