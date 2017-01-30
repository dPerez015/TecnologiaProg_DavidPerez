#pragma once
#include <utility>
#include <time.h>
#include "GridRect.h"
#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "LvlManager.h"



class Grid {
public:
	Grid() {}
	~Grid() {
		//delete[] theGrid;
	}
	void draw() {
		for (int i = 0; i < tamX; i++) {
			for (int j = 0; j < tamY;j++) {
				R.Push(theGrid[i][j]);
				SDL_RenderDrawRect(R.getRenderer(), &theGrid[i][j].rect);
				/*if (theGrid[i][j].type!=typeOfSquare::EMPTY) {
					R.Render();
				}*/
			}
		}
	}
	void update() {
		if (player.isAlive) {
			if (numFoodAppeared>numFood) {
				currLvl++;
				numFoodAppeared = 1;
				numFood = numFood + (incrementFood*currLvl);
				lvlLoad();
				playerInit();
			}
			
			//seleccionar la dir del player
			setPlayerDir();
			//mover al jugador
			movePlayer();
		}
		
	}
	

	//inicializacion de la grid
	void GridInit(dificulty &dif) {
		//incicializacion de variables en funcion de la dificultad
		switch (dif) {
		case dificulty::EASY:
			tamX = LvLM.defaultStats.numCol * 5;
			tamY = LvLM.defaultStats.numRows * 5;
			numFood = LvLM.defaultStats.numOfFood;
			incrementFood = LvLM.defaultStats.incrementFood;
			break;
		case dificulty::MEDIUM:
			tamX = LvLM.defaultStats.numCol * 2;
			tamY = LvLM.defaultStats.numRows * 2;
			numFood = LvLM.defaultStats.numOfFood * 2;
			incrementFood = LvLM.defaultStats.incrementFood * 2;
			break;
		case dificulty::HARD:
			tamX = LvLM.defaultStats.numCol ;
			tamY = LvLM.defaultStats.numRows ;
			numFood = LvLM.defaultStats.numOfFood*5;
			incrementFood = LvLM.defaultStats.incrementFood*5;
			break;
		default:
			break;
		}
		//nos situamos en el primer nivel.
		currLvl = 0;
		numFoodAppeared = 0;
		//variables del player que no se reinician al perder una vida
		player.punct = 0;
		player.vidas = 3;
		player.isAlive = true;
		//creamos la grid vacia
		gridCreation();
		//cargamos el nivel
		lvlLoad(/*dif*/);
		//playerinit
		playerInit();
		//random numbers;
		srand(time(NULL));

		
	}
	inline int getPunt() { return player.punct; }
	inline int getVidas() { return player.vidas; }
	inline bool isPAlive() { return player.isAlive; }
private:
#pragma region PRIV_METHODS
	void gridCreation() {
		//uso estas variables para que se entienda mejor el codigo
		//porcentage de margen
		float porCentX = 0.9;
		float porCentY = 0.7;
		//tamaño de los margenes (espacio que sobra/2)
		int margenX = W.GetWidth()*(1 - porCentX) / 2;
		int margenY = W.GetHeigth()*(1 - porCentY)/2 ;
		//tamaño de cada casilla(tamaño total/numero de casillas)
		int cellWidth = W.GetWidth()*porCentX / tamX;
		int cellHeight = W.GetHeigth()*porCentY / tamY;
		//grid vacia
		theGrid = new GridRect*[tamX];
		for (int i = 0; i < tamX; i++) {
			theGrid[i] = new GridRect[tamY];
			for (int j = 0; j < tamY; j++) {
				theGrid[i][j].rect.x = (i*cellWidth) + margenX;
				theGrid[i][j].rect.y = (j*cellHeight) + margenY;
				theGrid[i][j].rect.w = cellWidth;
				theGrid[i][j].rect.h = cellHeight;
				theGrid[i][j].type = typeOfSquare::EMPTY;
				theGrid[i][j].dir = direction::NONE;
				theGrid[i][j].flip = SDL_FLIP_NONE;
			}
		}
	}
	void lvlLoad(/*dificulty &dif*/) {
		for (int i = 0; i < tamX; i++) {
			for (int j = 0; j < tamY; j++) {
				//la inicializacion de niveles ha dejado de funcionar-.-"
				/*if (LvLM.levels[dif][currLvl][i][j] ) {
					theGrid[i][j].type = typeOfSquare::BLOCK;
				}*/
				theGrid[i][j].type = typeOfSquare::EMPTY;
			}
		}
		//para enseñar la capacidad que tiene nuestro codigo de generar mapas diversos haciendo 
		//uso de bloques modificaré manualmente 1 casilla, la de arriba a la izquierda.
		theGrid[0][0].type = typeOfSquare::BLOCK;

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


		createFood();


		player.dir = direction::DOWN;
		
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
		InMan.emptyArrows();
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
					player.vidas--;
					if (player.vidas <= 0) {
						player.isAlive = false;
					}
					lvlLoad();//deberia recargar el nivels, pero ya hemos dicho, no funciona
					playerInit();

					break;
				}
			}
			else {
				player.vidas--;
				if (player.vidas <= 0) {
					player.isAlive = false;
				}
				lvlLoad();
				playerInit();
				break;
			}

			break;
#pragma endregion 
#pragma region DIR_DOWN
		case direction::DOWN:
			if (player.head.second + 1 < tamY) {//si no se va a salir del mapa
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
					player.vidas--;
					if (player.vidas <= 0) {
						player.isAlive = false;
					}
					lvlLoad();
					playerInit();
					break;
				}
			}
			else {
				player.vidas--;
				if (player.vidas <= 0) {
					player.isAlive = false;
				}
				lvlLoad();
				playerInit();
				break;
			}

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
				default:
					player.vidas--;
					if (player.vidas <= 0) {
						player.isAlive = false;
					}
					lvlLoad();
					playerInit();
					break;
				}
			}
			else {
				player.vidas--;
				if (player.vidas <= 0) {
					player.isAlive = false;
				}
				lvlLoad();
				playerInit();
				break;
			}

			break;
#pragma endregion
#pragma region DIR_RIGHT
		case direction::RIGHT:
			if (player.head.first + 1 < tamX) {//si no se va a salir del mapa
				switch (theGrid[player.head.first + 1][player.head.second].type) {//hay algo raro en esa casilla?
				case typeOfSquare::EMPTY://si no hay nada
					moveTail();
					moveHead(+1, 0);
					break;
				case typeOfSquare::FOOD://si hay comida
					moveHead(+1, 0);
					createFood();
					break;
				default://se muere
					player.vidas--;
					if (player.vidas <= 0) {
						player.isAlive = false;
					}
					lvlLoad();
					playerInit();
					break;
				}
			}
			else {
				player.vidas--;
				if (player.vidas <= 0) {
					player.isAlive = false;
				}
				lvlLoad();
				playerInit();
				break;
			}

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
			theGrid[player.head.first][player.head.second].dir = player.dir;
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
			return entrada == direction::LEFT ? true : false;
			break;
		case direction::DOWN:
			return entrada == direction::RIGHT ? true : false;
			break;
		case direction::LEFT:
			return entrada == direction::DOWN ? true : false;
			break;
		case direction::RIGHT:
			return entrada == direction::UP ? true : false;
			break;
		}
	}
	void createFood() {
		numFoodAppeared++;
		player.punct += 100 * numFoodAppeared;
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
	
	int currLvl, numFoodAppeared;
	int tamX, tamY, numFood,incrementFood;
	GridRect **theGrid;
	struct Player {
		std::pair<int,int> head;
		std::pair<int,int>tail;
		direction dir;
		int punct;
		int vidas;
		bool isAlive;
	} player;
#pragma endregion
	
};

