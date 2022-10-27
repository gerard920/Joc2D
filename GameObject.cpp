
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "GameObject.h"
#include "MainPlayer.h"
#include "Enemy1.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define movH 1.f / 269.f
#define movV 1.f / 269.f

#define imageH 1472.f
#define imageW 1012.f



GameObject *GameObject::make_Object(int typeObject)
{
	if (typeObject == 0) {
		return new MainPlayer();
	}
	else if (typeObject == 1) {
		return new Enemy1();
	}
}

void GameObject::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	alive = true;
	tileMapDispl = tileMapPos;

}

void GameObject::update(int deltaTime) {
	cout << "1" << " is divisible by" << "2" << endl;
	sprite->update(deltaTime);
}

void GameObject::render()
{
	sprite->render();
}

void GameObject::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void GameObject::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 GameObject::getPosition() {
	return this->posPlayer;
}


