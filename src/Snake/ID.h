#pragma once

enum class  ObjectID { //enum class evita comparaciones con otros enum y permite especificar el tamaño de los datos (:const int), aunque si lo pongo ocurre un error de compilador (fatal error c1001)
	SNAKE, SNAKE_HEAD, SNAKE_BODY, SNAKE_TAIL, SNAKE_CURVA,COMIDA
};
