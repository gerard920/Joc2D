#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy1.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>



#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void Enemy1::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);

	spritesheet.loadFromFile("images/Enemy1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	setSizePlayer(glm::ivec2(46, 50));
	texProgram = &shaderProgram;


	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, texProgram);


	subiendo = true;
	bajando = false;
}

void Enemy1::update(int deltaTime)
{
	currentTime += deltaTime;

	GameObject::update(deltaTime);

	glm::ivec2 position = getPosition();


	if (subiendo) {
		if (map->collisionMoveUp(getPosition(), getSizePlayer())) {
			subiendo = false;
			bajando = true;
		}
		else {
			position.y -= 2;
		}
	}
	else if  (bajando) {
		if (map->collisionMoveDown(getPosition(), getSizePlayer())) {
			subiendo = true;
				bajando = false;
		}
		else {
			position.y += 2;
		}
	}
	
	setPosition(position);
}



int Enemy1::getType() {
	return 1;
}

bool Enemy1::detectColisionMap(glm::ivec2 posAnterior) {
	/*if (GameObject::detectColisionMap(posAnterior)) {
		this->setPosition(posAnterior);
		return true;
	}*/
	return false;

}

vector<GameObject*> Enemy1::disparar(ShaderProgram texProgram)
{

	vector<GameObject*> disparos;	
	if (1 + rand() % 100 == 1) {
		GameObject* bala1 = GameObject::make_Object(6);
		bala1->init(glm::ivec2(32, 16), texProgram);
		bala1->setPosition(glm::vec2(this->getPosition().x, this->getPosition().y));

		bala1->setTileMap(map);
		disparos.push_back(bala1);
	}

	return disparos;
}





