#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

class Outline
{
protected:
	RenderWindow window;
public:
	Outline(); // resolutions of x and y
	void draw_line(int x1, int y1, int x2, int y2, Color c, RenderTarget& target); // function to draw the boundary lines
	void load_map(char** map, int rows, int cols); // it will load the map on screen
};

class Basic
{
protected:
	Vector2i pos;
	Vector2i startPos;
	Texture* texture;
	CircleShape lives;
	int speed;
	char current_direction;
	char movement;     // i: up, k: down, j: left, l: right
public:

	Basic(); // default constructor
	int getSpeed(); // getter for speed
	char get_movement(); // getter for movement
	void set_movement(const char c);  // setter for movement
	Vector2i getStartPos();
	void setStartPos(Vector2i p);  // setter for start position
	virtual void getMove(Event& eve) = 0;  // pure virtual functions
	virtual void DrawWin(RenderTarget& Window, int index, float xPix = 0.f, float yPix = 0.f) = 0;
	void setDirection(char directionChar); // setter for direction
	char getDirection(Vector2i curr); // getter for direction
	void setPos(Vector2i vec);  /// setter for position
	Vector2i getPosition();
	Vector2i current_directionVector();
	Vector2i nextMoveVector(); // vector movement 
	Vector2i computePos(int x, int y);  // set position through vector
	int getDistance(Vector2i p1, Vector2i p2); // getter for distance
};

class Pacman :public Basic
{
protected:
	CircleShape* Basic;
public:

	Pacman(); // default constructor
	void getMove(Event& eve); // movement of pacman
	void DrawWin(RenderTarget& Window, int index, float xPix, float yPix); // it will draw the basic window
};

class Ghost :public Basic
{
protected:
	RectangleShape* Basic;
	Vector2i target;
	int strategy;
public:

	Ghost(int index, int strat); // parameterized constructor
	void SetTexture(int index); // function will set the texture using SFML classes
	void getMove(Event& eve);
	void DrawWin(RenderTarget& Window, int index, float xPix, float yPix); // it will draw the window
	void setTarget(Vector2i v); // setter for target
	int getStrategy();// getter for strategy
	Vector2i getTarget(int strat, Vector2i Positon);
	Vector2i getTarget();
};

class Draw_Map
{
protected:
	char** map;
	int rows, columns;
public:

	Draw_Map(); // default constructor 
	~Draw_Map(); // destructor
	bool readMapFile(const char* name, int& no_of_dots, int& no_of_boosters, Basic**& ahms);
	bool canPass(char c); // condition for pacman so it does not cross walls
	char getMapValue(Vector2i currPos, Vector2i nextMovVector); // returns the next character on the map player is trying to move to
};

class Functions : public Outline, public Draw_Map // main interface for the game
{
	Basic** baseArr;
	int no_of_dots;
	int no_of_ghosts, no_of_entities;
	float scaredTimer;
	bool isScared;   // check of scared status for ghost
	Clock clock;
public:
	Functions();  // default constructor 
	bool collision(); // it will handle collision of pacman with ghosts
	char ghost_moves(int index); // ghost movement and their path
	void Update(); // function will update the position of ghosts to initial positions after collision
	void run(); // main function which will run the program
};