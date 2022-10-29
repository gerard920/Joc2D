#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



void MainPlayer::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	GameObject::init(tileMapPos, shaderProgram);
	spritesheet.loadFromFile("images/rType.png", TEXTURE_PIXEL_FORMAT_RGBA);

	setSizePlayer(glm::ivec2(86, 86));

	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(0.33, 0.19), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_UP, 10);
	sprite->addKeyframe(STAND_UP, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_DOWN, 10);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_UP, 10);
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_DOWN, 10);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
}

void MainPlayer::update(int deltaTime)
{

	glm::ivec2 position = getPosition();
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		/*if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);*/
		position.x -= 2;
		/*if (map->collisionMoveLeft(position, glm::ivec2(64, 64)))
		{
			position.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}*/
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		/*if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);*/
		position.x += 2;
		/*if (map->collisionMoveRight(position, glm::ivec2(64, 64)))
		{
			position.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}*/
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{/*
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);*/
		position.y -= 2;
		/*if (map->collisionMoveUp(position, glm::ivec2(64, 64)))
		{
			position.y += 2;
			sprite->changeAnimation(STAND_UP);
		}*/
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		/*if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);*/
		position.y += 2;
		/*if (map->collisionMoveDown(position, glm::ivec2(64, 64)))
		{
			position.y -= 2;
			sprite->changeAnimation(STAND_DOWN);
		}*/
	}
	/*else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else if (sprite->animation() == MOVE_UP)
			sprite->changeAnimation(STAND_UP);
		else if (sprite->animation() == MOVE_DOWN)
			sprite->changeAnimation(STAND_DOWN);
	}*/
	setPosition(position);

	GameObject::update(deltaTime);
}

int MainPlayer::getType() {
	return 0;
}

bool MainPlayer::detectColisionMap(glm::ivec2 posAnterior) {
	if (GameObject::detectColisionMap(posAnterior)) {
		this->setPosition(posAnterior);
		return true;
	}
	return false;
	
}

