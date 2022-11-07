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
	spritesheet.loadFromFile("images/EnemyShoot.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	setSizePlayer(glm::ivec2(21, 6));

	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.339f));
	sprite->changeAnimation(0);
	//rotacio
}

void EnemyShoot1::update(int deltaTime)
{
	GameObject::update(deltaTime);

	glm::ivec2 position = getPosition();

	int subtype = this->getSubtype();
	switch (subtype) {
	case 0:
		position.x -= 1;
		position.y -= 1;
		break;
	case 1:
		position.x -= 1;
		break;
	case 2:
		position.x -= 1;
		position.y += 1;
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