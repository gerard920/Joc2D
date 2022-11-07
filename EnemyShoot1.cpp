#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "EnemyShoot1.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void EnemyShoot1::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);
	//Mida prsj	           //mida sheet que agafa 
	if (getSubtype() == 3) {
		setSizePlayer(glm::ivec2(16, 32));
		spritesheet.loadFromFile("images/EnemyShootDown.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);

	}
	else {
		spritesheet.loadFromFile("images/EnemyShoot2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		setSizePlayer(glm::ivec2(32, 16));
		sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	}
}

void EnemyShoot1::update(int deltaTime)
{
	GameObject::update(deltaTime);

	glm::ivec2 position = getPosition();

	int subtype = this->getSubtype();
	switch (subtype) {
	case 0:
		position.x -= 2;
		position.y -= 2;
		break;
	case 1:
		position.x -= 2;
		break;
	case 2:
		position.x -= 2;
		position.y += 2;
		break;
	case 3:
		position.y += 2;
		break;


	}


	setPosition(position);
}



int EnemyShoot1::getType() {
	return 6;
}

bool EnemyShoot1::detectColisionMap(glm::ivec2 posAnterior) {
	if (GameObject::detectColisionMap(posAnterior)) {
		quitarVida();
		return true;
	}
	return false;
}