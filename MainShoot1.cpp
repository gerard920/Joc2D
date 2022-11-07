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
	if (this->getSubtype() != 1) {
		spritesheet.loadFromFile("images/Shoot.png", TEXTURE_PIXEL_FORMAT_RGBA);
		setSizePlayer(glm::ivec2(32, 16));
	}
	else {
		spritesheet.loadFromFile("images/SuperShoot.png", TEXTURE_PIXEL_FORMAT_RGBA);
		this->setLives(4);
		setSizePlayer(glm::ivec2(45, 25));
	}
	//Mida prsj	           //mida sheet que agafa 
	
	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	/*sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.339f));
	sprite->changeAnimation(0);*/
}

void MainShoot1::update(int deltaTime)
{
	GameObject::update(deltaTime);

	glm::ivec2 position = getPosition();

	int subtype = this->getSubtype();
	switch (subtype) {
	case 2:
		position.x += 2;
		position.y -= 2;
		break;
	case 0:
	case 1:
		position.x += 2;
		break;
	case 3:
		position.x += 2;
		position.y += 2;
		break;

	}

	setPosition(position);


}



int MainShoot1::getType() {
	return 5;
}

bool MainShoot1::detectColisionMap(glm::ivec2 posAnterior) {
	if (GameObject::detectColisionMap(posAnterior)) {
		quitarVida();
		return true;
	}
	return false;	
}