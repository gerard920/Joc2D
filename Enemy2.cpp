#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy2.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>


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

	glm::mat4 modelview;
	glm::vec2 position = sprite->getPosition();

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	modelview = glm::translate(modelview, glm::vec3(46.f, 50.f, 0.f));
	modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-46.f, -50.f, 0.f));
	modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	sprite->render(2, currentTime, modelview);

	position.x = modelview[3].x;
	position.y = modelview[3].y;
	this->setPosition2(position);
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




