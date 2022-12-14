#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "MenuPrincipal.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	bool canColission(int objectX, int objectY);

	int getGameLives();
	void setGameLives(int gameLives);

	int getStatusGame();
	void setStatusGame(int statusGame);

	enum SatusGame {
		Playing = 0,
		Lose = 1,
		Win = 2
	};


private:
	bool bPlay;                       // Continue to play game?
	Scene *scene;                      // Scene to render
	MenuPrincipal *menu;                // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time

	bool inMenu, inPlay;
	int idSceneMenu;
	int statusGame;

	int gameLives;
	bool resetScene;
	bool collisionMatrix[9][9] = {
		//P, E1, E2, E3, E4, SP, SE, BOSS, Force
		 {0,  1,  1,  1,  1,  0,  1, 1, 0},
		 {1,  0,  0,  0,  0,  1,  0, 0, 1},
		 {1,  0,  0,  0,  0,  1,  0, 0, 1},
		 {1,  0,  0,  0,  0,  1,  0, 0, 1},
		 {1,  0,  0,  0,  0,  1,  0, 0, 1},
		 {0,  1,  1,  1,  1,  0,  1, 1, 0},
		 {1,  0,  0,  0,  0,  1,  0, 0, 1},
		 {1,  1,  1,  1,  1,  0,  1, 0, 1},
		 {0,  1,  1,  1,  1,  0,  1, 1, 0},

	};

};


#endif // _GAME_INCLUDE


