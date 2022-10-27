#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init()
{
	bPlay = true; inMenu = true; inPlay = false;
	idSceneMenu = 0;

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
			if (getKey(99)) { //C --> pantalla Creditos
				idSceneMenu = 1;				
			}
			else if (getKey(105)) { //I --> pantalla Creditos
				idSceneMenu = 2;
			}
			else if (getKey(106)) { //J --> Nos vamos a la escena de jugar
				delete scene;
				scene = new Scene();
				scene->init();
				inPlay = true;
				inMenu = false;
			}
		}
		else if (idSceneMenu == 1 || idSceneMenu == 2) {
			if (getKey(109)) { // M
				idSceneMenu = 0;
			}
		}
		menu->update(deltaTime, idSceneMenu);
	}	
	else if (inPlay) {
		if (getKey(109)) { //M --> Volvemos al menu
			idSceneMenu = 0;
			delete menu;
		    menu = new MenuPrincipal();
			menu->init(idSceneMenu);
			inPlay = false;
			inMenu = true;
		
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
	return collisionMatrix[objectX, objectY];
}





