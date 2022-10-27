#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy1.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void Enemy1::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/rType.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	sprite = Sprite::createSprite(glm::ivec2(86, 86), glm::vec2(0.3, 0.18), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.339f));
	subiendo = true;
	bajando = false;
	sprite->changeAnimation(0);
	//tileMapDispl = tileMapPos;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy1::update(int deltaTime)
{
	sprite->update(deltaTime);

	glm::ivec2 position = getPosition();


	if (subiendo) {
		if (position.y >= 0) {
			position.y -= 2;
		}
		else {
			position.y += 2;
			subiendo = false;
			bajando = true;
		}
	}
	else if (bajando) {
		if (position.y <= SCREEN_HEIGHT - 86) {
			position.y += 2;
		}
		else {
			position.y -= 2;
			subiendo = true;
			bajando = false;
		}
	}
	setPosition(position);
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}



