#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Force.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void Force::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);
	spritesheet.loadFromFile("images/Force.png", TEXTURE_PIXEL_FORMAT_RGBA);
	setSizePlayer(glm::ivec2(46, 46));
	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	this->setLives(1000000);
	
}

void Force::update(int deltaTime)
{
	GameObject::update(deltaTime);
	
	glm::ivec2 mainPosition = this->getMainPlayerPos();
	mainPosition.x += 40;
	setPosition(mainPosition);
}



int Force::getType() {
	return 8;
}

bool Force::detectColisionMap(glm::ivec2 posAnterior) {
	if (GameObject::detectColisionMap(posAnterior)) {
		quitarVida();
		return true;
	}
	return false;
}