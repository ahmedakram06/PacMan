#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;
using namespace sf;

Outline::Outline() :window(VideoMode(495, 545), "PACMAN")  // resolutions of x and y
	{
	}
void Outline::draw_line(int x1, int y1, int x2, int y2, Color c, RenderTarget& target) // function to draw the boundary lines
	{
		Vertex arr[4];  // colors of boundary lines
		arr[0].color = Color::Yellow;
		arr[1].color = Color::Blue;
		arr[2].color = Color::Blue;
		arr[3].color = Color::Yellow;
		if (x1 == x2)
		{
			arr[0].position = Vector2f(18.f * (x1)-2.f, 18.f * (y1));
			arr[1].position = Vector2f(18.f * (x1)+2.f, 18.f * (y1));
			arr[2].position = Vector2f(18.f * (x1)+2.f, 18.f * (y2));
			arr[3].position = Vector2f(18.f * (x1)-2.f, 18.f * (y2));
		}
		else if (y1 == y2)
		{
			arr[0].position = Vector2f(18.f * (x1), 18.f * (y1)-2.f);
			arr[1].position = Vector2f(18.f * (x1), 18.f * (y1)+2.f);
			arr[2].position = Vector2f(18.f * (x2), 18.f * (y1)+2.f);
			arr[3].position = Vector2f(18.f * (x2), 18.f * (y1)-2.f);
		}
		target.draw(arr, 4, Quads);
	}
	void Outline::load_map(char** map, int rows, int cols) // it will load the map on screen
	{
		for (int x = 0; x < rows - 1; ++x)
		{
			if ((map[x][0] == 'w') && (map[x + 1][0] == 'w')) draw_line(x, 0, x + 1, 0, Color::Red, window);
			if ((map[x][30] == 'w') && (map[x + 1][30] == 'w')) draw_line(x, 30, x + 1, 30, Color::Red, window);
		}
		for (int y = 0; y < cols - 1; ++y)
		{
			if ((map[0][y] == 'w') && (map[0][y + 1] == 'w')) draw_line(0, y, 0, y + 1, Color::Red, window);
			if ((map[27][y] == 'w') && (map[27][y + 1] == 'w')) draw_line(27, y, 27, y + 1, Color::Red, window);
		}
		for (int x = 1; x < rows - 1; x++)
			for (int y = 1; y < cols - 1; y++)
			{
				if (map[x][y] == 'w')  // w is used for walls in text file
				{
					if (map[x - 1][y] == 'w') draw_line(x - 1, y, x, y, Color::Red, window);
					if (map[x + 1][y] == 'w') draw_line(x + 1, y, x, y, Color::Red, window);
					if (map[x][y - 1] == 'w') draw_line(x, y - 1, x, y, Color::Red, window);
					if (map[x][y + 1] == 'w') draw_line(x, y + 1, x, y, Color::Red, window);
				}
			}
		for (int x = 0; x < rows; x++)
		{
			for (int y = 0; y < cols; y++)
			{
				if (map[x][y] == 'd')  // d is used for pallets or food of pacman
				{
					CircleShape s(2.0f);
					s.setOrigin(2, 2);
					s.setFillColor(Color::White);
					s.setPosition(Vector2f(((18.f * x)), (18.f * y)));
					window.draw(s);
				}
				else if (map[x][y] == 'b') // b is used for the energizer in text file
				{
					CircleShape s(5.0f);
					s.setOrigin(5, 5);
					s.setFillColor(Color::Blue);
					s.setPosition(Vector2f((18.f * x), (18.f * y)));
					window.draw(s);
				}
			}
		}
	}

	Basic::Basic()  // default constructor
	{
		texture = new  Texture;
		texture->loadFromFile("C:\\Users\\Lenovo\\Desktop\\Ahmed Assigments\\2nd Semester\\Pac man Project\\pacman ali\\Resources\\spritesheet\\spritesheet1.png");
		current_direction = '\0';
		speed = 1;
		movement = '\0';
	}
	int Basic::getSpeed()  // getter for speed
	{
		return speed;
	}
	char Basic::get_movement() 
	{ return movement; } // getter for movement

	void Basic::set_movement(const char c) 
	{ movement = c; }  // setter for movement

	Vector2i Basic::getStartPos() 
	{ return startPos; }

	void Basic::setStartPos(Vector2i p) 
	{ startPos = p; }  // setter for start position
	
	void Basic::setDirection(char directionChar) // setter for direction
	{
		current_direction = directionChar;
	}

	char Basic::getDirection(Vector2i curr) // getter for direction
	{
		if (curr.x == 1)return 'l';
		if (curr.x == -1)return 'j';
		if (curr.y == 1)return 'k';
		if (curr.y == -1)return 'i';
		return 'l';
	}

	void Basic::setPos(Vector2i vec) 
	{ pos = vec; }  // setter for position

	Vector2i Basic::getPosition()
	{
		return pos;
	}
	Vector2i Basic::current_directionVector()
	{
		switch (current_direction)
		{
		case 'i': return  Vector2i(0, -1); //up
		case 'k': return  Vector2i(0, 1);  //down
		case 'j': return  Vector2i(-1, 0);	//left
		case 'l': return  Vector2i(1, 0);	//right
		}
		return  Vector2i(0, 0);
	}

	Vector2i Basic::nextMoveVector() // vector movement 
	{
		switch (movement)
		{
		case 'i': return  Vector2i(0, -1);
		case 'k': return  Vector2i(0, 1);
		case 'j': return  Vector2i(-1, 0);
		case 'l': return  Vector2i(1, 0);
		}
		return  Vector2i(0, 0);
	}
	Vector2i Basic::computePos(int x, int y)  // set position through vector
	{
		pos = Vector2i((18 * x), (18 * y));
		return pos;
	}
	int Basic::getDistance(Vector2i p1, Vector2i p2) // getter for distance
	{
		return ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)); // pythagoras theorem
	}

	Pacman::Pacman() // default constructor
	{
		Basic = new  CircleShape[2];
		int rectLeft = 0, rectTop = 0;
		for (int i = 0; i < 2; i++)
		{
			Basic[i].setRadius(12);
			Basic[i].setOrigin(12, 12);
			Basic[i].setTexture(texture);
			Basic[i].setTextureRect(IntRect(rectLeft, rectTop, 56, 60));
			rectLeft = 0;
			rectTop = 68;
		}
	}
	void Pacman::getMove(Event& eve) // movement of pacman
	{
		Basic[0].setScale(1.f, 1.f);
		Basic[1].setScale(1.f, 1.f);
		switch (eve.key.code)  // switch statements for four possible outcomes
		{
		case  Keyboard::Up:
			current_direction = 'i';
			movement = 'i';
			Basic[0].setRotation(270.f);
			Basic[1].setRotation(270.f);
			break;
		case  Keyboard::Down:
			movement = 'k';
			current_direction = 'k';
			Basic[0].setRotation(90.f);
			Basic[1].setRotation(90.f);
			break;
		case  Keyboard::Left:
			movement = 'j'; current_direction = 'j';
			Basic[0].setScale(1.f, -1.f);
			Basic[0].setRotation(180.f);
			Basic[1].setScale(1.f, -1.f);
			Basic[1].setRotation(180.f);
			break;
		case  Keyboard::Right:
			movement = 'l'; current_direction = 'l';
			Basic[0].setRotation(0.f);
			Basic[1].setRotation(0.f);
			break;
		default:
			movement = '\0'; current_direction = '\0'; break;
		}
	}
	void Pacman::DrawWin(RenderTarget& Window, int index, float xPix, float yPix) // it will draw the basic window
	{
		int x = pos.x, y = pos.y;
		Basic[index].setPosition(x, y);
		Window.draw(Basic[index]);
	}

	Ghost::Ghost(int index, int strat) // parameterized constructor
	{
		Basic = new  RectangleShape[2];
		strategy = strat;
		for (int i = 0; i < 2; i++)
		{
			Basic[i].setSize(Vector2f(25, 30)); // set the size of enemy
			Basic[i].setOrigin(12.5, 15); // set its initial position
			Basic[i].setTexture(texture); // set the texture
		}
		SetTexture(index);
		current_direction = 'k';
	}
	void Ghost::SetTexture(int index) // function will set the texture using SFML classes
	{
		int rectTop = 130, rectHeight = 40;
		if (index == 2)
			rectTop += 42;
		Basic[0].setTextureRect(IntRect(0, rectTop, 35, rectHeight));
		if (index == 1)
			rectTop += 85;
		else if (index == 2)
			rectTop += 44;
		Basic[1].setTextureRect(IntRect(0, rectTop, 35, rectHeight));
	}
	void Ghost::getMove(Event& eve)
	{
	}
	void Ghost::DrawWin(RenderTarget& Window, int index, float xPix, float yPix) // it will draw the window
	{
		int x = pos.x, y = pos.y;
		Basic[index].setPosition(x, y);
		Window.draw(Basic[index]);
	}
	void Ghost::setTarget(Vector2i v) { target = v; } // setter for target
	int Ghost::getStrategy() { return strategy; } // getter for strategy
	Vector2i Ghost::getTarget(int strat, Vector2i Positon)
	{
		Positon /= 16;
		return Positon;
	}
	Vector2i Ghost::getTarget() { return target; }

	Draw_Map::Draw_Map() // default constructor 
	{
		map = nullptr;
		rows = 0;
		columns = 0;
	}
	Draw_Map::~Draw_Map() // destructor
	{
		if (map != nullptr)
		{
			for (int i = 0; i < rows; i++)
			{
				delete[]map[i];
				map[i] = nullptr;
			}
			delete[]map;
			map = nullptr;
		}
	}
	bool Draw_Map::readMapFile(const char* name, int& no_of_dots, int& no_of_boosters, Basic**& ahms)
	{                                   // function will read the map from text file and display it on screen
		if (map != nullptr)
			this->~Draw_Map();
		no_of_dots = 0;
		no_of_boosters = 0;
		ifstream fin(name);
		if (fin.is_open()) // condition if file is open
		{
			if (fin >> rows)
			{
				if (!(fin >> columns))
					return false;
				fin.ignore();
			}
			else
				return false;   // if file is not opened
			map = new char* [rows];
			for (int i = 0; i < rows; i++)
				map[i] = new char[columns + 1];
			int rowNo = 0, x = 0, y = 0;
			string str = "";
			int i = 1;
			while (fin.eof() == false)
			{
				str = "";
				fin >> str;
				for (x = 0; x < 28 && x < str.length(); x++)
				{
					map[x][y] = str[x];
					switch (str[x])
					{
					case 'd':no_of_dots++; break;
					case 'b': no_of_boosters++; break;
					case 'p':ahms[0]->setStartPos(ahms[0]->computePos(x, y));  break;
					case 'g': if (i < 3) ahms[i]->setStartPos(ahms[i]->computePos(x, y));  i++; break;
					}
				}
				rowNo++; y++;
			}
			return true;
		}
		else
			return false;
	}
	bool Draw_Map::canPass(char c) // condition for pacman so it does not cross walls
	{
		if (c == 'w')
			return false;
		return true;
	}
	char Draw_Map::getMapValue(Vector2i currPos, Vector2i nextMovVector)  // returns the next character on the map player is trying to move to
	{
		currPos *= 18;
		currPos /= 18;
		int x = currPos.x + nextMovVector.x, y = currPos.y + nextMovVector.y;
		if (x != min(max(0, x), rows - 1) || (y != min(max(0, y), columns - 1)))
			return 'w';
		return map[x][y];
	}

	Functions::Functions() : Outline(), Draw_Map()  // default constructor 
	{
		no_of_dots = 0;
		no_of_ghosts = 2;
		isScared = false;
		scaredTimer
			= 0.f;
		no_of_entities = 1 + no_of_ghosts;    // +1 is the player
		baseArr = new Basic * [no_of_entities];
		baseArr[0] = new Pacman;
		int s = 1;
		for (int i = 1; i < no_of_entities; i++, s /= 2)
			baseArr[i] = new Ghost(i, s);
	}
	bool Functions::collision() // it will handle collision of pacman with ghosts
	{
		for (int i = 1; i < no_of_entities; i++)
			if (baseArr[i]->getPosition() / 18 == baseArr[0]->getPosition() / 18)
			{
				if (isScared)
				{
					baseArr[i]->setPos(baseArr[i]->getStartPos());
				}
				return true;
			}
		return false;
	}
	char Functions::ghost_moves(int index) // ghost movement and their path
	{
		Vector2i target = static_cast<Ghost*>(baseArr[index])->getTarget();
		int strat = static_cast<Ghost*>(baseArr[index])->getStrategy();
		int totalPath = 4, available = 0;
		Vector2i curr = baseArr[index]->getPosition() / 18;
		Vector2i* possiblePaths = new  Vector2i[totalPath];
		if (Draw_Map::canPass(Draw_Map::getMapValue(curr, Vector2i(1, 0))) == true)
		{
			possiblePaths[available] = (curr + Vector2i(1, 0));
			available++;
		}
		if (Draw_Map::canPass(Draw_Map::getMapValue(curr, Vector2i(-1, 0))) == true)
		{
			possiblePaths[available] = (curr + Vector2i(-1, 0));
			available++;
		}
		if (Draw_Map::canPass(Draw_Map::getMapValue(curr, Vector2i(0, 1))) == true)
		{
			possiblePaths[available] = (curr + Vector2i(0, 1));
			available++;
		}
		if (Draw_Map::canPass(Draw_Map::getMapValue(curr, Vector2i(0, -1))) == true)
		{
			possiblePaths[available] = (curr + Vector2i(0, -1));
			available++;
		}
		for (int i = 0; i < available && available>1; i++)
		{
			if (possiblePaths[i] == curr - baseArr[index]->current_directionVector())  // ghost cant turn back
			{
				Vector2i* temp = new  Vector2i[available - 1];
				for (int j = 0, k = 0; j < available; j++)
				{
					if (j != i)
					{
						temp[k] = possiblePaths[j];
						k++;
					}
				}
				available--;
				delete[]possiblePaths;
				possiblePaths = new  Vector2i[available];
				for (int j = 0; j < available; j++)
					possiblePaths[j] = temp[j];
				delete[]temp;
				temp = nullptr;
				break;
			}
		}
		int min_dis_index = -1;
		int dist = INT_MAX;
		if (strat == 1 && isScared == false)  // for direct pursuit, choose shortest possible path
		{
			for (int u = 0; u < available; u++)
			{
				int x = baseArr[index]->getDistance(target, possiblePaths[u]);
				if (dist > x)
				{
					dist = x;
					min_dis_index = u;
				}
			}
		}
		else     // for random pursuit, chose one of the available paths at random
		{
			int lowerBound = 0, upperBound = available - 1;
			min_dis_index = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
		}

		if (min_dis_index != -1)
			return baseArr[index]->getDirection((possiblePaths[min_dis_index] - curr));
		else
			return (baseArr[index]->getDirection(-1 * baseArr[index]->current_directionVector()));
	}
	void Functions::Update() // function will update the position of ghosts to initial positions after collision
	{
		int i = 0;
		Vector2i update = baseArr[0]->current_directionVector();
		int speed = baseArr[0]->getSpeed();
		Vector2i temp = baseArr[0]->getPosition();
		Vector2i temp4 = temp / 18;
		temp = baseArr[0]->getPosition();
		temp4.x = temp.x % 18; temp4.y = temp.y % 18;
		if (Draw_Map::map[temp.x / 18][temp.y / 18] == 'd' || Draw_Map::map[temp.x / 18][temp.y / 18] == 'b')
		{
			Vector2i temp2 = (temp / 18);
			char curr = Draw_Map::map[temp2.x][temp2.y];
			switch (curr)
			{
			case 'd':
				map[temp2.x][temp2.y] = 'e';
				no_of_dots--;
				break;
			case 'b':
				map[temp2.x][temp2.y] = 'e';
				isScared = true;
				no_of_dots--;
				scaredTimer = 30.f;
				break;
			}
			if (baseArr[0]->get_movement() != '\0' && Draw_Map::canPass(Draw_Map::getMapValue((temp / 18), baseArr[0]->nextMoveVector())))
			{
				baseArr[0]->setDirection(baseArr[0]->get_movement());
				baseArr[0]->set_movement('\0');
			}
			if (!Draw_Map::canPass(Draw_Map::getMapValue(temp / 18, baseArr[0]->current_directionVector())))
			{
				baseArr[0]->setDirection('\0');
			}
			baseArr[0]->set_movement('\0');
			update = baseArr[0]->current_directionVector();
		}
		for (i; i < speed; i++)
			if (Draw_Map::canPass(Draw_Map::getMapValue(baseArr[0]->getPosition() / 18, baseArr[0]->current_directionVector())))
				baseArr[0]->setPos(baseArr[0]->getPosition() + update);

		// updating ghosts
		for (int x = 1; x < no_of_entities; x++)
		{
			update = baseArr[x]->current_directionVector();
			speed = baseArr[x]->getSpeed();
			for (i = 0; i < speed; i++);
			{
				if (Draw_Map::canPass(Draw_Map::getMapValue(baseArr[x]->getPosition() / 18, update)))
					baseArr[x]->setPos(baseArr[x]->getPosition() + update);
				temp = baseArr[x]->getPosition();
				int strat = static_cast<Ghost*>(baseArr[x])->getStrategy();
				Vector2i targ = static_cast<Ghost*>(baseArr[x])->getTarget(strat, baseArr[0]->getPosition());
				static_cast<Ghost*>(baseArr[x])->setTarget(targ);
				baseArr[x]->set_movement(ghost_moves(x));
				baseArr[x]->setDirection(baseArr[x]->get_movement());
			}

		}
	}
	int fileNo = 0;
	void Functions::run() // main function which will run the program
	{
		srand(time(0));
		int no_of_dots, no_of_boosters = 0;
		Draw_Map::readMapFile("C:\\Users\\Lenovo\\Desktop\\Ahmed Assigments\\2nd Semester\\Pac man Project\\pacman ali\\Resources\\spritesheet\\level.txt", no_of_dots, no_of_boosters, baseArr);
		no_of_dots = no_of_dots + no_of_boosters;
		Time timeSinceLastUpdate = Time::Zero, timePerFrame(seconds(1.f / 60.f));
		baseArr[0]->setDirection('\0');
		baseArr[0]->set_movement('\0');
		while (Outline::window.isOpen()) // condition if the window is opened or not
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::KeyPressed)
				{
					switch (event.key.code) // keys for movement of pacman
					{
					case  Keyboard::Up:
					case  Keyboard::Down:
					case  Keyboard::Left:
					case  Keyboard::Right:
						baseArr[0]->getMove(event); break;
					default:
						baseArr[0]->setDirection('\0');
						baseArr[0]->set_movement('\0');
					}
				}
			}
			window.clear(Color(0, 0, 0)); // set the background color
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate >= timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				if (scaredTimer > 0)
					scaredTimer -= 1.f / 80.f;
				else
					isScared = false;
				Update();
				if (collision()) // collision of pacman and ghost
				{
					if (!isScared) // when ghost is not in scared mode
					{
						cout << "GAME OVER!!" << endl;
						system("pause");
					}
				}
			}
			load_map(Draw_Map::map, Draw_Map::rows, Draw_Map::columns);
			int index = isScared ? 1 : 0;
			for (int i = 0; i < no_of_entities; i++)
				baseArr[i]->DrawWin(window, index);
			window.display();
		}
	}