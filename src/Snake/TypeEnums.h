#pragma once

enum class  ObjectID { //enum class evita comparaciones con otros enum y permite especificar el tamaño de los datos (:const int), aunque si lo pongo ocurre un error de compilador (fatal error c1001)
	SNAKE_FOOD, BLOCK
};
enum class typeOfSquare {
	EMPTY, HEAD, BODY, TAIL, CURVE, FOOD, BLOCK
};
enum class direction {
	UP, LEFT, DOWN, RIGHT, NONE
};
enum class dificulty {
	EASY, MEDIUM, HARD
};

