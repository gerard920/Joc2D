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
#define INIT_PLAYER_Y_TILES 12

#define INIT_ENEMY_X_TILES 30
#define INIT_ENEMY_Y_TILES 16



Scene::Scene()
{
	map = NULL;
	objects = vector<GameObject*>();
}

Scene::~Scene()
{
	if (map != NULL)
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
	initialTime = 0.f;
	initialPos = 0.f;
	mapPositionEsquerra = 0.f;
	shoot = false;
	//fons negre
	//declarar el fons
	glm::vec2 geom1[2] = { glm::vec2(0.f, 0.f), glm::vec2(2250.f, 480.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fons = TexturedQuad::createTexturedQuad(geom1, texCoords2, texProgram);
	// Load textures
	//tex1.loadFromFile("images/fonsnegre.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//declarar el fons
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(2250.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	// Load textures
	tex.loadFromFile("images/mapita.png", TEXTURE_PIXEL_FORMAT_RGBA);

	map = TileMap::createTileMap("levels/level011.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	//Player
	GameObject *mainPlayer = GameObject::make_Object(MainPlayer);
	mainPlayer->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	mainPlayer->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	mainPlayer->setTileMap(map);
	objects.push_back(mainPlayer);
	posMainPlayer = mainPlayer->getPosition();

	GameObject *enemigo = GameObject::make_Object(1);
	enemigo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemigo->setPosition(glm::vec2((INIT_ENEMY_X_TILES * map->getTileSize()), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemigo->setTileMap(map);
	objects.push_back(enemigo);

	//GameObject *enemigo1 = GameObject::make_Object(2);
	//enemigo1->init(glm::vec2(((INIT_ENEMY_X_TILES + 4) * map->getTileSize()), INIT_ENEMY_Y_TILES * map->getTileSize()), texProgram);
	/////enemigo1->setPosition(glm::vec2(((INIT_ENEMY_X_TILES + 4 ) * map->getTileSize()), INIT_ENEMY_Y_TILES * map->getTileSize()));
	//enemigo1->setTileMap(map);
	//objects.push_back(enemigo1);

	//GameObject *enemigo2 = GameObject::make_Object(3);
	//enemigo2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//enemigo2->setPosition(glm::vec2(((INIT_ENEMY_X_TILES + 8) * map->getTileSize()), INIT_ENEMY_Y_TILES * map->getTileSize()));
	//enemigo2->setTileMap(map);
	//objects.push_back(enemigo2);

	GameObject *enemigo3 = GameObject::make_Object(4);
	enemigo3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemigo3->setPosition(glm::vec2(((INIT_ENEMY_X_TILES + 4) * map->getTileSize()), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemigo3->setTileMap(map);
	objects.push_back(enemigo3);




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

	//al clicar el 1,2,3
	if (Game::instance().getKey(49)) {
		initialPos = 200.f;
		initialTime = currentTime;
		mapPositionEsquerra == 200.f;
		objects[0]->setPosition(glm::ivec2(initialPos, INIT_PLAYER_Y_TILES * map->getTileSize()));
	}

	if (Game::instance().getKey(50)) {
		initialPos = 600.f;
		initialTime = currentTime;
		mapPositionEsquerra == 600.f;
		objects[0]->setPosition(glm::ivec2(initialPos, INIT_PLAYER_Y_TILES * map->getTileSize()));

	}

	if (Game::instance().getKey(51)) {
		initialPos = 1000.f;
		initialTime = currentTime;
		mapPositionEsquerra == 1000.f;
		objects[0]->setPosition(glm::ivec2(initialPos, INIT_PLAYER_Y_TILES * map->getTileSize()));

	}


	//I or i invulnerable
	if (Game::instance().getKey(73) || Game::instance().getKey(105)) {
		for (int i = 0; i < objects.size(); ++i) {
			if (objects[i]->getType() == MainPlayer) {
				objects[i]->setInvulnerable(!objects[i]->getInvulnerable());
			}
		}
	}

	//F or f force
	if (Game::instance().getKey(70) || Game::instance().getKey(102)) {
		for (int i = 0; i < objects.size(); ++i) {
			if (objects[i]->getType() == MainPlayer) {
			}
		}
	}

	//X or x shoot
	/*if ((Game::instance().getKey(88) || Game::instance().getKey(120)) && (currentTime - lastShootPlayer) / 1000 >= 1) {
		lastShootPlayer = currentTime;

		GameObject *shoot1 = GameObject::make_Object(MainPlayerShoot);
		shoot1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		shoot1->setPosition(glm::vec2((posMainPlayer.x + 46), posMainPlayer.y + 46 / 2 - 4 / 2));
		shoot1->setTileMap(map);
		objects.push_back(shoot1);
	}*/

	if (Game::instance().getKey(88) || Game::instance().getKey(120)) {
		timeXPressed += 1;
	}
	else {
		if (shoot) {
			shoot = false;
			GameObject *shoot1;
			if (timeXPressed < 50) {
				shoot1 = GameObject::make_Object(MainPlayerShoot);
				shoot1->setSubtype(0);
				
			}
			else {
				shoot1 = GameObject::make_Object(MainPlayerShoot);	
				shoot1->setSubtype(1);
			}
			shoot1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			shoot1->setPosition(glm::vec2((posMainPlayer.x + 46), posMainPlayer.y + 46 / 2 - 4 / 2));
			shoot1->setTileMap(map);
			objects.push_back(shoot1);
		}
		timeXPressed = 0;
	}

	if (timeXPressed > 0) {
		shoot = true;
	}



	/*if (1 + rand() % 200 == 1) {
		GameObject *enemigo = GameObject::make_Object(1 + rand() % 4);
		enemigo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemigo->setPosition(glm::vec2((INIT_ENEMY_X_TILES * map->getTileSize()) + currentTime / 100, INIT_ENEMY_Y_TILES * map->getTileSize()));
		enemigo->setTileMap(map);
		objects.push_back(enemigo);
	}
*/

	for (int i = 0; i < objects.size(); ++i) {

		glm::ivec2 posAnterior = objects[i]->getPosition();
		int currentFlame = 5;
		if (objects[i]->getType() == Enemy1) {
			if (1 + rand() % 200 == 1) {
				GameObject* bala1 = GameObject::make_Object(6);
				bala1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				bala1->setPosition(glm::vec2(posAnterior.x, posAnterior.y + 46 / 2 - 4 / 2));
				bala1->setTileMap(map);
				objects.push_back(bala1);
			}
		}
		/*if (objects[i]->getType() == Enemy2) {
			if (1 + rand() % 200 == 1) {
				GameObject* bala1 = GameObject::make_Object(6);
				bala1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				bala1->setPosition(glm::vec2(posAnterior.x, posAnterior.y + 46 / 2 - 4 / 2));
				bala1->setTileMap(map);
				objects.push_back(bala1);
			}
		}
		if (objects[i]->getType() == Enemy3) {
			if (1 + rand() % 200 == 1) {
				GameObject* bala1 = GameObject::make_Object(6);
				bala1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				bala1->setPosition(glm::vec2(posAnterior.x, posAnterior.y + 46 / 2 - 4 / 2));
				bala1->setTileMap(map);
				objects.push_back(bala1);
			}
		}*/
		if (objects[i]->getType() == Enemy4) {
			if (1 + rand() % 200 == 1) {
				GameObject* bala1 = GameObject::make_Object(6);
				bala1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				bala1->setPosition(glm::vec2(objects[i]->getPosition().x, objects[i]->getPosition().y + 46 / 2 - 4 / 2));
				bala1->setTileMap(map);
				bala1->setSubtype(0);
				GameObject* bala2 = GameObject::make_Object(6);
				bala2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				bala2->setPosition(glm::vec2(objects[i]->getPosition().x, objects[i]->getPosition().y + 46 / 2 - 4 / 2));
				bala2->setTileMap(map);
				bala2->setSubtype(1);
				GameObject* bala3 = GameObject::make_Object(6);
				bala3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				bala3->setPosition(glm::vec2(objects[i]->getPosition().x, objects[i]->getPosition().y + 46 / 2 - 4 / 2));
				bala3->setTileMap(map);
				bala3->setSubtype(2);

				objects.push_back(bala1);
				objects.push_back(bala2);
				objects.push_back(bala3);	

			}
		}

		objects[i]->update(deltaTime);
		objects[i]->detectColisionMap(posAnterior);
		objects[i]->detectColisionObject(objects, i);

		if (objects[i]->getType() == MainPlayer) {
			posMainPlayer = objects[i]->getPosition();
			if (mapPositionEsquerra >= objects[i]->getPosition().x) {
				objects[i]->setPosition(glm::ivec2(mapPositionEsquerra, objects[i]->getPosition().y));
			}
		}

		if (!objects[i]->isAlive()) {
			if (objects[i]->getType() == 0) {			
				Game::instance().setGameLives(Game::instance().getGameLives() - 1);
			}
			deleteObject(i);
		}

	}

}

void Scene::render()
{
	fons->render(tex1);
	map->render();
	texQuad->render(tex);

	float distance = (currentTime - initialTime) / 125;
	if (initialPos + (currentTime - initialTime) / 125 < 1001.f) {
		mapPositionEsquerra = initialPos + (currentTime - initialTime) / 125;
		projection = glm::ortho(initialPos + distance, float(SCREEN_WIDTH - 1 + distance + initialPos), float(SCREEN_HEIGHT - 1), 0.f);
	}

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);

	glm::mat4 modelview;
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, -glm::pi<float>() / 4, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview);
	for (int i = 0; i < objects.size(); ++i) {
		if (objects[i]->getType() == 6) {
			int subtype = objects[i]->getSubtype();
			switch (subtype) {
				case 0:
					
					break;
				case 2:					
					modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
					modelview = glm::rotate(modelview, -glm::pi<float>()/4, glm::vec3(0.0f, 0.0f, 1.0f));
					modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
					texProgram.setUniformMatrix4f("modelview", modelview);
					break;
			}
		}
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
