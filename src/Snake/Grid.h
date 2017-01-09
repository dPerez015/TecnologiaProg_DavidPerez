#pragma once
#include <utility>
#include "GridRect.h"
#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include <time.h>

class Grid {
public:
	Grid(int numOfRows, int numOfColumns):tamX(numOfColumns),tamY(numOfRows) {//una vez tengamos el xml solo necesitare el nombre del archivo
		//parte xML, coger el numero de columnas y filas

		//inicializacion de la grid vacia
		GridInit();
		//creacion del nivel 

		//inicializacion del player
		playerInit();
		
		//srand para la creacion de la comida.
		srand(time(NULL));
	}
	Grid() {}
	~Grid() {}
	void draw() {
		for (int i = 0; i < tamX; i++) {
			for (int j = 0; j < tamY;j++) {
				R.Push(theGrid[i][j]);
			}
		}
	}
	void update() {
		if (player.isAlive) {
			//seleccionar la dir del player
			setPlayerDir();
			//mover al jugador
			movePlayer();
		}
		else {
		//morir
		}
	}
	
private:
#pragma region PRIV_METHODS
	//inicializacion de la grid
	void GridInit() {
		//uso estas variables para que se entienda mejor el codigo
		//porcentage de margen
		float porCentX = 0.9;
		float porCentY = 0.7;
		//tamaño de los margenes (espacio que sobra/2)
		int margenX = W.GetWidth()*(1 - porCentX) / 2;
		int margenY = W.GetHeigth()*(1 - porCentY) / 2;
		//tamaño de cada casilla(tamaño total/numero de casillas)
		int cellWidth = W.GetWidth()*porCentX / tamX;
		int cellHeight = W.GetHeigth()*porCentY / tamY;

		theGrid = new GridRect*[tamX];
		for (int i = 0; i < tamX; i++) {
			theGrid[i] = new GridRect[tamY];
			for (int j = 0; j < tamY; j++) {
				theGrid[i][j].rect.x = i*cellWidth + margenX;
				theGrid[i][j].rect.y = j*cellHeight + margenY;
				theGrid[i][j].rect.w = cellWidth;
				theGrid[i][j].rect.h = cellHeight;
				theGrid[i][j].type = typeOfSquare::EMPTY;
				theGrid[i][j].dir = direction::NONE;
				theGrid[i][j].flip = SDL_FLIP_NONE;
			}
		}
	}

	//inicializacion del player en las coordenadas por defecto
	void playerInit() {
		theGrid[1][1].type = typeOfSquare::TAIL;
		theGrid[1][1].dir = direction::DOWN;
		player.tail.first = 1;
		player.tail.second = 1;
		theGrid[1][2].type = typeOfSquare::BODY;
		theGrid[1][2].dir = direction::DOWN;
		theGrid[1][3].type = typeOfSquare::HEAD;
		theGrid[1][3].dir = direction::DOWN;
		player.head.first = 1;
		player.head.second = 3;


		theGrid[1][6].type = typeOfSquare::FOOD;
		theGrid[1][6].dir = direction::UP;


		player.dir = direction::DOWN;
		player.punct = 0;

		player.isAlive = true;
	};
	//direccion del player
	void setPlayerDir() {
		bool seted = false;
		while (!seted && InMan.lastArrowPressed.size() != 0) {
			if (canDirChange(InMan.lastArrowPressed.top())) { 
				player.dir = InMan.lastArrowPressed.top(); 
				seted = true;
			}
			else { 	InMan.lastArrowPressed.pop();}
		}
	}
	bool canDirChange(direction newDir) {
		switch (newDir) {
			case direction::UP:
				if (player.dir == direction::DOWN)return false;
				else return true;
				break;
			case direction::DOWN:
				if (player.dir == direction::UP)return false;
				else return true;
				break;
			case direction::LEFT:
				if (player.dir == direction::RIGHT)return false;
				else return true;
				break;
			case direction::RIGHT:
				if (player.dir == direction::LEFT)return false;
				else return true;
				break;
			default:
				break;
		}
	}
	//mover el player en funcion de su direccion
	void movePlayer() {
		//comprovamos la direccion
		switch (player.dir) {
		#pragma region DIR_UP
		case direction::UP:
			if (player.head.second - 1 >= 0) {//si no se va a salir del mapa
				switch (theGrid[player.head.first][player.head.second - 1].type) {//hay algo raro en esa casilla?
				case typeOfSquare::EMPTY://si no hay nada
					moveTail();//primero movemos la cola para no "chocarnos" con ella
					moveHead(0, -1);//movemos la cabeza 
					break;
				case typeOfSquare::FOOD://si hay comida
					// solo movemos la cabeza y dejamos la cola, asi alargamos la serpiente 
					moveHead(0, -1);
					//creamos una nueva comida
					createFood();
					break;
				default://si es tail, body o curba (teoricamente tambien cabeza, pero no va a pasar)
					player.isAlive = false;
					break;
				}
			}
			else player.isAlive = false;

			break;
#pragma endregion 
		#pragma region DIR_DOWN
		case direction::DOWN:
			if (player.head.second + 1 >= 0) {//si no se va a salir del mapa
				switch (theGrid[player.head.first][player.head.second + 1].type) {//hay algo raro en esa casilla?
				case typeOfSquare::EMPTY://si no hay nada
					moveTail();
					moveHead(0, 1);
					break;
				case typeOfSquare::FOOD://si hay comida
					moveHead(0, 1);
					createFood();
					break;
				default://se muere
					player.isAlive = false;
					break;
				}
			}
			else player.isAlive = false;

			break;
		#pragma endregion
		#pragma region DIR_LEFT
		case direction::LEFT:
			if (player.head.first - 1 >= 0) {//si no se va a salir del mapa
				switch (theGrid[player.head.first - 1][player.head.second].type) {//hay algo raro en esa casilla?
				case typeOfSquare::EMPTY://si no hay nada
					moveTail();
					moveHead(-1, 0);
					break;
				case typeOfSquare::FOOD://si hay comida
					moveHead(-1, 0);
					createFood();
					break;
				default://se muere
					player.isAlive = false;
					break;
				}
			}
			else player.isAlive = false;

			break;
#pragma endregion
		#pragma region DIR_RIGHT
		case direction::RIGHT:
			if (player.head.first - 1 >= 0) {//si no se va a salir del mapa
				switch (theGrid[player.head.first - 1][player.head.second].type) {//hay algo raro en esa casilla?
				case typeOfSquare::EMPTY://si no hay nada
					moveTail();
					moveHead(-1, 0);
					break;
				case typeOfSquare::FOOD://si hay comida
					moveHead(-1, 0);
					createFood();
					break;
				default://se muere
					player.isAlive = false;
					break;
				}
			}
			else player.isAlive = false;
			break;
#pragma endregion
		}
	}
	//mover cola y la cabeza (usados en movePlayer)
	void moveTail() {
		//miramos la direccion de la cola
		switch (theGrid[player.tail.first][player.tail.second].dir){
			case direction::UP:
				//no hace falta comprobar si podemos ir hacia una direccion (sabemos que si)
				//vaciamos la casilla en la que estamos y "eliminamos" la direccion
				theGrid[player.tail.first][player.tail.second].type = typeOfSquare::EMPTY;
				theGrid[player.tail.first][player.tail.second].dir = direction::NONE;
				theGrid[player.tail.first][player.tail.second].flip = SDL_FLIP_NONE;
				//colocamos la cola
				theGrid[player.tail.first][player.tail.second - 1].type = typeOfSquare::TAIL;//solo hemos de mover, la direccion ya esta decidida
				theGrid[player.tail.first][player.tail.second - 1].flip = SDL_FLIP_NONE;
				//cambiamos las coordenadas 
				player.tail.second--;
				break;
			case direction::DOWN:
				//vaciamos casilla
				theGrid[player.tail.first][player.tail.second].type = typeOfSquare::EMPTY;
				theGrid[player.tail.first][player.tail.second].dir = direction::NONE;
				theGrid[player.tail.first][player.tail.second].flip = SDL_FLIP_NONE;
				//colocamos la cola
				theGrid[player.tail.first][player.tail.second + 1].type = typeOfSquare::TAIL;
				theGrid[player.tail.first][player.tail.second + 1].flip = SDL_FLIP_NONE;
				//cambiamos coord																	 
				player.tail.second++;
				break;
			case direction::LEFT:
				//vaciamos casilla
				theGrid[player.tail.first][player.tail.second].type = typeOfSquare::EMPTY;
				theGrid[player.tail.first][player.tail.second].dir = direction::NONE;
				theGrid[player.tail.first][player.tail.second].flip = SDL_FLIP_NONE;
				//colocamos la cola
				theGrid[player.tail.first-1][player.tail.second].type = typeOfSquare::TAIL;
				theGrid[player.tail.first-1][player.tail.second].flip = SDL_FLIP_NONE;
				//cambiamos coord																	 
				player.tail.first--;
				break;
			case direction::RIGHT:
				//vaciamos casilla
				theGrid[player.tail.first][player.tail.second].type = typeOfSquare::EMPTY;
				theGrid[player.tail.first][player.tail.second].dir = direction::NONE;
				//colocamos la cola y eliminamos su flip (si lo tenia por ser una curva)
				theGrid[player.tail.first + 1][player.tail.second].type = typeOfSquare::TAIL;
				theGrid[player.tail.first + 1][player.tail.second].flip = SDL_FLIP_NONE;
				//cambiamos coord																	 
				player.tail.first++;
				break;
		}
	}
	void moveHead(int8_t movesX, int8_t movesY) {
		//si la direccion actual es = a la dir con la que entramos es recto
		if (player.dir == theGrid[player.head.first][player.head.second].dir) {
			//colocamos body en la casilla actual
			theGrid[player.head.first][player.head.second].type = typeOfSquare::BODY;
			//su direccion de salida ya esta bien colocada (no ga girado) 
			//recolocamos la cabeza
			theGrid[player.head.first + movesX][player.head.second + movesY].type = typeOfSquare::HEAD;
			//"seteamos" su direccion de entrada, que nos sirve para saber si ha girado en esa casilla concreta
			theGrid[player.head.first + movesX][player.head.second + movesY].dir = player.dir;
			//cambiamos las coordenadas
			player.head.first += movesX;
			player.head.second += movesY;
		}
		//si no, hay una curva
		else {
			//colocamos curve en al casilla actual
			theGrid[player.head.first][player.head.second].type = typeOfSquare::CURVE;
			//comprovamos si hemos de girar el sprite
			if (hasToFlip(theGrid[player.head.first][player.head.second].dir)) {
				theGrid[player.head.first][player.head.second].flip = SDL_FLIP_HORIZONTAL;
			}
			//asiganmos la direccion de salida 
			theGrid[player.head.first + movesX][player.head.second + movesY].dir = player.dir;
			//recolocamos la cabeza
			theGrid[player.head.first + movesX][player.head.second + movesY].type = typeOfSquare::HEAD;
			//"seteamos" su direccion de entrada, que nos sirve para saber si ha girado en esa casilla concreta
			theGrid[player.head.first + movesX][player.head.second + movesY].dir = player.dir;
			//cambiamos las coordenadas
			player.head.first += movesX;
			player.head.second += movesY;
		}
	}
	//dependiendo de la direccion de salida determina si se ha de girar el sprite de la curva;
	bool hasToFlip(direction entrada) {
		switch (player.dir){
		case direction::UP:
			return entrada == direction::LEFT ? false : true;
			break;
		case direction::DOWN:
			return entrada == direction::RIGHT ? false : true;
			break;
		case direction::LEFT:
			return entrada == direction::DOWN ? false : true;
			break;
		case direction::RIGHT:
			return entrada == direction::UP ? false : true;
			break;
		}
	}
	void createFood() {
		bool isCreated = false;
		int x, y;
		while (!isCreated) {
			x = rand()%(tamX-1);
			y = rand()%(tamY-1);
			if (theGrid[x][y].type == typeOfSquare::EMPTY) {
				theGrid[x][y].type = typeOfSquare::FOOD;
				theGrid[x][y].dir = direction::UP;
				isCreated = true;
			}

		}
	}

#pragma endregion
#pragma region PRIV_VAR
	int tamX, tamY;
	GridRect **theGrid;
	struct Player {
		std::pair<int,int> head;
		std::pair<int,int>tail;
		direction dir;
		int punct;
		bool isAlive;
	} player;
#pragma endregion
	
};

