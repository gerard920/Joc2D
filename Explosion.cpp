#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Explosion.h"
#include "Game.h"




void Explosion::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/Explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//Mida prsj	           //mida sheet que agafa 
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1, 1), &spritesheet, &shaderProgram);
}

void Explosion::update(int deltaTime)
{
	sprite->update(deltaTime);	
}

void Explosion::render()
{
	sprite->render();
}

void Explosion::setPosition(const glm::vec2 &pos)
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void  Explosion::setTime(int time) {
	this->time = time;
}
int  Explosion::getTime() {
	return this->time;
}



