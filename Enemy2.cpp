#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy2.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void Enemy2::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);

	spritesheet.loadFromFile("images/Enemy2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	setSizePlayer(glm::ivec2(46, 50));
	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	initialPosition = getPosition();
}

void Enemy2::update(int deltaTime)
{
	currentTime += deltaTime;

	GameObject::update(deltaTime);

	//glm::ivec2 position = getPosition();

	//rad = 40;
	//position.x = (initialPosition.x + rad) * cos(currentTime/150 % 180);
	//position.y = (initialPosition.y + rad) * sin(currentTime/150 % 180);

	//setPosition(position);
}

void Enemy2::render() {	
	sprite->render(1, currentTime);

}

int Enemy2::getType() {
	return 2;
}

bool Enemy2::detectColisionMap(glm::ivec2 posAnterior) {
	/*if (GameObject::detectColisionMap(posAnterior)) {
		this->setPosition(posAnterior);
		return true;
	}*/
	return false;

}




