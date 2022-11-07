#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init()
{
	bPlay = true; inMenu = true; inPlay = false; resetScene = false;
	idSceneMenu = 0;

	gameLives = 3;

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene = new Scene();
	scene->init();

	menu = new MenuPrincipal();
	menu->init(idSceneMenu);


}

bool Game::update(int deltaTime)
{

	//Para entrar a jugar
	if (inMenu) {
		if (idSceneMenu == 0) {
			if (getKey(99) || getKey(67)) { //C --> pantalla Creditos
				idSceneMenu = 1;				
			}
			else if (getKey(105) || getKey(73)) { //I --> pantalla Creditos
				idSceneMenu = 2;
			}
			else if (getKey(80) || getKey(112)) { //P --> Nos vamos a la escena de play
				delete scene;
				scene = new Scene();
				scene->init();
				inPlay = true;
				inMenu = false;
			}
		}
		else if (idSceneMenu == 1 || idSceneMenu == 2 || idSceneMenu == 3 || idSceneMenu == 4) {
			if (getKey(109) || getKey(77)) { // M
				idSceneMenu = 0;
			}
		}		
		menu->update(deltaTime, idSceneMenu);
	}	
	else if (inPlay) {
		if (resetScene) {
			resetScene = false;
			delete scene;
			scene = new Scene();
			scene->init();
			inPlay = true;
			inMenu = false;
		}
		if ((getKey(109) || getKey(77)) || statusGame == 1 || statusGame == 2) { //M --> Volvemos al menu
			gameLives = 3;
			delete menu;
		    menu = new MenuPrincipal();
			if (statusGame == 1) {
				idSceneMenu = 3;
				menu->init(idSceneMenu);

			}
			else if (statusGame == 2) {
				idSceneMenu = 4;
				menu->init(idSceneMenu);

			}
			else {
				idSceneMenu = 0;
				menu->init(idSceneMenu);
			}
			inPlay = false;
			inMenu = true;

		}		
		if (gameLives == 0) {
			statusGame = 1;		
		}

		scene->update(deltaTime);
	}

	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (inPlay) {
		scene->render();
	}
	else if(inMenu) {
		menu->render();
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::canColission(int objectX, int objectY) {
	return collisionMatrix[objectX][objectY];
}


int Game::getGameLives() {
	return this->gameLives;
}
void Game::setGameLives(int gameLives) {
	this->gameLives = gameLives;
	resetScene = true;
}


int Game::getStatusGame() {
	return this->statusGame;
}
void Game::setStatusGame(int statusGame) {
	this->statusGame = statusGame;
}

