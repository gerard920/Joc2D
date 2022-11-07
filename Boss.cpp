#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Boss.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void Boss::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);

	spritesheet.loadFromFile("images/Boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	setSizePlayer(glm::ivec2(280, 353));
	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);

	this->setLives(40);
}

void Boss::update(int deltaTime)
{
	GameObject::update(deltaTime);
}

int Boss::getType() {
	return 7;
}






