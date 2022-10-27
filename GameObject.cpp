
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "GameObject.h"
#include "MainPlayer.h"
#include "Enemy1.h"
#include "MainShoot1.h"

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
	else if (typeObject == 2) {
		return new MainShoot1();
	}
}

void GameObject::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	alive = true;
	tileMapDispl = tileMapPos;
	lives = 1;
}

void GameObject::update(int deltaTime) {
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

int GameObject::getType() {
	return -1;
}

bool GameObject::detectColisionObject(vector<GameObject*> objects, int index) {
	for (int i = index; i < objects.size(); ++i) {
		if (canColision(type, objects[i]->getType())) {

		}

	}
	return false;
}

bool GameObject::detectColisionMap() {
	return false;
}

bool GameObject::isAlive() {
	return alive;
}

bool GameObject::canColision(int objectX, int objectY) {
	return Game::instance().canColission(objectX, objectY);
}
