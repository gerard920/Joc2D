
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
#include "TileMap.h"

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

glm::ivec2 GameObject::getSizePlayer() {
	return this->sizePlayer;
}


void GameObject::setSizePlayer(const glm::vec2 &size) {
	this->sizePlayer = size;
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

bool GameObject::detectColisionObject(vector<GameObject*> objects ,int index) {
	for (int i = index +1 ; i < objects.size(); ++i) {
		if (canColision(objects[index]->getType(), objects[i]->getType())) {
			if ((collisionMoveUp(posPlayer, sizePlayer, objects[i]->getPosition(), objects[i]->getSizePlayer()) || collisionMoveDown(posPlayer, sizePlayer, objects[i]->getPosition(), objects[i]->getSizePlayer())
				|| collisionMoveRight(posPlayer, sizePlayer, objects[i]->getPosition(), objects[i]->getSizePlayer()) || collisionMoveLeft(posPlayer, sizePlayer, objects[i]->getPosition(), objects[i]->getSizePlayer()))) {

				quitarVida();
				objects[i]->quitarVida();
			}
		}
	}
	return false;
}

bool GameObject::detectColisionMap(glm::ivec2 posAnterior) {
	return (map->collisionMoveUp(posPlayer, sizePlayer) || map->collisionMoveDown(posPlayer, sizePlayer) || map->collisionMoveRight(posPlayer, sizePlayer) || map->collisionMoveLeft(posPlayer, sizePlayer));
}

bool GameObject::isAlive() {
	return alive;
}

void GameObject::setAlive(bool alive) {
	this->alive = alive;
}

bool GameObject::canColision(int objectX, int objectY) {
	return Game::instance().canColission(objectX, objectY);
}

void GameObject::quitarVida() {
	lives--;
	if (lives <= 0) {
		alive = false;
	}
}

bool GameObject::collisionMoveLeft(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const
{
	int xObj1, y0Obj1, y1Obj1;
	int x0Obj2, x1Obj2, y0Obj2, y1Obj2;

	xObj1 = posObj1.x;
	y0Obj1 = posObj1.y;
	y1Obj1 = posObj1.y + sizeObj1.y;

	x0Obj2 = posObj2.x;
	x1Obj2 = posObj2.x + sizeObj2.x;
	y0Obj2 = posObj2.y;
	y1Obj2 = posObj2.y + sizeObj2.y;

	if (xObj1 >= x0Obj2 && xObj1 <= x1Obj2) {
		if ((y0Obj1 >= y0Obj2 && y0Obj1 <= y1Obj2) || y1Obj1 >= y0Obj2 && y1Obj1 <= y1Obj2) {
			return true;
		}
	}

	return false;
}

bool GameObject::collisionMoveRight(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const
{
	int xObj1, y0Obj1, y1Obj1;
	int x0Obj2, x1Obj2, y0Obj2, y1Obj2;

	xObj1 = posObj1.x + sizeObj1.x;
	y0Obj1 = posObj1.y;
	y1Obj1 = posObj1.y + sizeObj1.y;

	x0Obj2 = posObj2.x;
	x1Obj2 = posObj2.x + sizeObj2.x;
	y0Obj2 = posObj2.y;
	y1Obj2 = posObj2.y + sizeObj2.y;

	if (xObj1 >= x0Obj2 && xObj1 <= x1Obj2) {
		if ((y0Obj1 >= y0Obj2 && y0Obj1 <= y1Obj2) || y1Obj1 >= y0Obj2 && y1Obj1 <= y1Obj2) {
			return true;
		}
	}	

	return false;
}

bool GameObject::collisionMoveUp(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const
{
	int x0Obj1, x1Obj1, yObj1;
	int x0Obj2, x1Obj2, y0Obj2, y1Obj2;

	x0Obj1 = posObj1.x;
	x1Obj1 = posObj1.x + sizeObj1.x;
	yObj1 = posObj1.y;

	x0Obj2 = posObj2.x;
	x1Obj2 = posObj2.x + sizeObj2.x;
	y0Obj2 = posObj2.y;
	y1Obj2 = posObj2.y + sizeObj2.y;

	if (yObj1 >= y0Obj2 && yObj1 <= y1Obj2) {
		if ((x0Obj1 >= x0Obj2 && x0Obj1 <= x1Obj2) || (x1Obj1 >= x0Obj2 && x1Obj1 <= x1Obj2)) {
			return true;
		}
	}

	return false;
}

bool GameObject::collisionMoveDown(const glm::ivec2 &posObj1, const glm::ivec2 &sizeObj1, const glm::ivec2 &posObj2, const glm::ivec2 &sizeObj2) const
{
	int x0Obj1, x1Obj1, yObj1;
	int x0Obj2, x1Obj2, y0Obj2, y1Obj2;

	x0Obj1 = posObj1.x;
	x1Obj1 = posObj1.x + sizeObj1.x;
	yObj1 = posObj1.y + sizeObj1.y;

	x0Obj2 = posObj2.x;
	x1Obj2 = posObj2.x + sizeObj2.x;
	y0Obj2 = posObj2.y;
	y1Obj2 = posObj2.y + sizeObj2.y;

	if (yObj1 >= y0Obj2 && yObj1 <= y1Obj2) {
		if ((x0Obj1 >= x0Obj2 && x0Obj1 <= x1Obj2) || (x1Obj1 >= x0Obj2 && x1Obj1 <= x1Obj2)) {
			return true;
		}
	}

	return false;
}

