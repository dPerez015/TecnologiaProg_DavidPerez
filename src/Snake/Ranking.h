#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

#define BinF BinaryFiles::Instance()

//Struct de personas que guarda la persona y la puntuacion
struct HighScores {
	std::string name;
	int score;
};

class BinaryFiles {
private:
	BinaryFiles() {}
	~BinaryFiles() {}
public:
	static BinaryFiles &Instance() {
		static BinaryFiles bin;
		return bin;
	}
	//Funcion que ordena a un nuevo jugador en la posicion que le toca
	void setNewRank(HighScores &newRank) {
		for (int i = 0; i < 10; i++) {
			if (top10[i].score < newRank.score) {
				for (int j = 9; j > i; j--) {
					top10[j] = top10[j - 1];
				}
				top10[i] = newRank;
				break;
			}
		}
	}
	//Funcion encargada de escribir el array en el fichero binario
	void writeBin(std::string name, int score) {


		std::ifstream readFile("../../res/Ranking.bin", std::ios::binary);
		//En este for leemos el fichero binario ya escrito y les pasamos el contenido de este al array
		for (int i = 0; i < 10; i++) {
			std::getline(readFile, top10[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&top10[i].score), sizeof(top10[i].score));
		}

		readFile.close();
		//Variable tipo struct que guarda los parametros de la funcion
		HighScores toIns;
		toIns.name = name;
		toIns.score = score;

		//sort();//Llamada a la funcion que ordena el array
		setNewRank(toIns);//Llamada a la funcion que pone al nuevo jugador en la posicion del array pertinente

		std::ofstream writeFile("../../res/Ranking.bin", std::ios::binary);
		//Escribimos el array en el fichero binario
		for (int i = 0; i < 10; i++) {
			writeFile.write(top10[i].name.c_str(), top10[i].name.size());
			writeFile.write("\0", sizeof(char));
			writeFile.write(reinterpret_cast<char*>(&top10[i].score), sizeof(top10[i].score));
		}
		writeFile.close();

	}
	//Funcion que devuelbe un array con el contenido del fichero
	HighScores readBin(int posicion) {
		std::ifstream readFile("../../res/Ranking.bin", std::ios::binary);
		//En este for leemos el fichero binario ya escrito y les pasamos el contenido de este al array
		for (int i = 0; i < 10; i++) {
			std::getline(readFile, top10[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&top10[i].score), sizeof(top10[i].score));
		}

		readFile.close();
		return top10[posicion];
	}
	

private:
	//Array de 10 posiciones que servira para passar los jugadores al fichero y leerlo despues 

	HighScores top10[10];
};