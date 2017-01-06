#pragma once
#include <utility>
#include "GridRect.h"
#include "Window.h"
class Grid {
public:
	Grid(int numOfCells) {//una vez tengamos el xml solo necesitare el nombre del archivo
		//parte xML, coger el numero de columnas y filas

		//inicializacion de la grid vacia
		GridInit(numOfCells);
		//inicializacion del player

	}
	~Grid() {}
	void draw() {}
	void update() {}
	void movePlayer() {
		//comprovamos la direccion
		switch (player.dir) {
		#pragma region DIR_UP
		case direction::UP:
			if (player.head.second - 1 >= 0) {//si no se va a salir del mapa
				switch (theGrid[player.head.first][player.head.second-1].type) {//hay algo raro en esa casilla?
					case typeOfSquare::EMPTY://si no hay nada
						moveTail();//primero movemos la cola para no "chocarnos" con ella
						moveHead(0,-1);//movemos la cabeza 
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
				switch (theGrid[player.head.first-1][player.head.second].type) {//hay algo raro en esa casilla?
				case typeOfSquare::EMPTY://si no hay nada
					moveTail();
					moveHead(-1, 0);
					break;
				case typeOfSquare::FOOD://si hay comida
					moveHead(-1, 0);
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
	inline void setPlayerDir(direction dir) { player.dir = dir; }
private:
#pragma region PRIV_METHODS
	void GridInit(int numOfCells) {
		//uso estas variables para que se entienda mejor el codigo
		//porcentage de margen
		float porCentX = 0.9;
		float porCentY = 0.7;
		//tamaño de los margenes (espacio que sobra/2)
		int margenX = W.GetWidth*(1 - porCentX) / 2;
		int margenY = W.GetHeigth*(1 - porCentY) / 2;
		//tamaño de cada casilla(tamaño total/numero de casillas)
		int cellWidth = W.GetWidth*porCentX / numOfCells;
		int cellHeight = W.GetHeigth*porCentY / numOfCells;

		theGrid = new GridRect*[numOfCells];
		for (int i = 0; i < numOfCells; i++) {
			theGrid[i] = new GridRect[numOfCells];
			for (int j = 0; j < numOfCells; j++) {
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
			player.head.first += movesY;
			player.head.second += movesY;
		}
		//si no hay una curva
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
			player.head.first += movesY;
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
	void createFood() {}
#pragma endregion
#pragma region PRIV_VAR
	GridRect **theGrid;
	struct Player {
		std::pair<int,int> head;
		std::pair<int,int>tail;
		direction dir;
		bool isAlive;
	} player;
#pragma endregion
	
};

