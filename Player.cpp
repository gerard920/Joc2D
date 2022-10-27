#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f

enum PlayerAnims {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,
	STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	this->init(tileMapPos, shaderProgram, 0);
}


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int type)
{
	//this->type = type;	
    alive = true;
	loadSpriteSheet(type, shaderProgram, tileMapPos);
	tileMapDispl = tileMapPos;	
}

void Player::update(int deltaTime)
{
	moveObject(deltaTime);
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Player::getXPlayer() {
	return this->posPlayer.x;
}


int Player::getYPlayer() {
	return this->posPlayer.y;
}

void Player::loadSpriteSheet(int type, ShaderProgram &shaderProgram, const glm::ivec2 &tileMapPos ) {
	spritesheet.loadFromFile("images/rType.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	if (type == 0) { //Player
											//Mida prsj	           //%sheet que agafa 
		sprite = Sprite::createSprite(glm::ivec2(86, 86), glm::vec2(0.33, 0.19), &spritesheet, &shaderProgram);

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
	else if (type == 1) { //Bala
		sprite = Sprite::createSprite(glm::ivec2(86, 86), glm::vec2(0.33, 0.19), &spritesheet, &shaderProgram);		
	}
}

void Player::moveObject(int deltaTime) {
	if (type == 0) {
		sprite->update(deltaTime);
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 64)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			if (sprite->animation() != MOVE_UP)
				sprite->changeAnimation(MOVE_UP);
			posPlayer.y -= 2;
			/*if (map->collisionMoveUp(posPlayer, glm::ivec2(64, 64)))
			{
				posPlayer.y += 2;
				sprite->changeAnimation(STAND_UP);
			}*/
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (sprite->animation() != MOVE_DOWN)
				sprite->changeAnimation(MOVE_DOWN);
			posPlayer.y += 2;
			/*if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 64)))
			{
				posPlayer.y -= 2;
				sprite->changeAnimation(STAND_DOWN);
			}*/
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == MOVE_UP)
				sprite->changeAnimation(STAND_UP);
			else if (sprite->animation() == MOVE_DOWN)
				sprite->changeAnimation(STAND_DOWN);
		}
	}
	else if (type == 1) {
		sprite->update(deltaTime);
		posPlayer.x += 2;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}





