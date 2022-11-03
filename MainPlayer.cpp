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
	spritesheet.loadFromFile("images/MainPlayer.png", TEXTURE_PIXEL_FORMAT_RGBA);

	setSizePlayer(glm::ivec2(46, 46));

	sprite = Sprite::createSprite(getSizePlayer(), glm::vec2(1, 1), &spritesheet, &shaderProgram);
}

void MainPlayer::update(int deltaTime)
{


	glm::ivec2 position = getPosition();
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		position.x -= 2;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		position.x += 2;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		position.y -= 2;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		position.y += 2;
	}
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

