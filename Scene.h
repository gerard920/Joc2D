#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "GameObject.h"
#include "Explosion.h"
#include "TexturedQuad.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();	

private:
	void initShaders();

private:
	TileMap *map;
	vector<GameObject*> objects;
	vector<Explosion*> explosiones;
	Texture tex1;
	Texture tex;
	TexturedQuad *texQuad;
	TexturedQuad *fons;

	enum TypeObject {
		MainPlayer = 0,
		Enemy1 = 1,
		Enemy2 = 2,
		Enemy3 = 3,
		Enemy4 = 4,
		MainPlayerShoot = 5,
		EnemyShoot = 6,
		Boss = 7,
		Force = 8
	};

	ShaderProgram texProgram;
	float currentTime;
	float initialTime;
	float initialPos;
	float mapPositionEsquerra;
	float timeXPressed;
	bool shoot;
	bool forceActivated;
	bool shootForceBuff;
	int timeForce;
	glm::mat4 projection;
	glm::ivec2 posMainPlayer;
	int radiusMainPlayer;

	bool f200, f300, f400, f500, f600, f700, f800;

	int lastShootPlayer;
	int timeLapShoot;

	void deleteObject(int indexObject);
	void apretarTecla();
	void posicionarObjetos();
	void switchCaseInTypeOfObject(int i, glm::vec2 posAnterior);
};


#endif // _SCENE_INCLUDE

