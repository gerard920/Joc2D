#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainShoot1.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void MainShoot1::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);
	spritesheet.loadFromFile("images/rType.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	setSizePlayer(glm::ivec2(86, 86));
	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(0.3, 0.18), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.339f));
	sprite->changeAnimation(0);
}

void MainShoot1::update(int deltaTime)
{
	GameObject::update(deltaTime);

	glm::ivec2 position = getPosition();
	position.x += 2;
	setPosition(position);
}



int MainShoot1::getType() {
	return 2;
}

bool MainShoot1::detectColisionMap(glm::ivec2 posAnterior) {
	if (GameObject::detectColisionMap(posAnterior)) {
		setAlive(false);
		return true;
	}
	return false;	
}