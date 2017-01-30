#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using std::ios;

namespace BinaryFiles {
	//Struct de personas que guarda la persona y la puntuacion
	struct HighScores {
		std::string name;
		int score;
	};
	//Array de 10 posiciones que servira para passar los jugadores al fichero y leerlo despues 
	HighScores top10[10];

	void sort() {//Funcion que ordena el array

		HighScores sortRank;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (top10[i].score > top10[j].score) {
					sortRank = top10[i];
					top10[i] = top10[j];
					top10[j] = sortRank;
				}
			}
		}
	}
	//Funcion que ordena a un nuevo jugador en la posicion que le toca
	void setNewRank(HighScores &newRank) {
		for (int i = 0; i < 10; i++) {
			if (top10[i].score < newRank.score) {
				for (int j = 10 - 1; j > i; j--) {
					top10[j] = top10[j - 1];
				}
				top10[i] = newRank;
				break;
			}
		}
	}
	//Funcion encargada de escribir el array en el fichero binario
	void writeBin(std::string name, int score) {


		std::ifstream readFile("../res/Ranking.bin", ios::binary);
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

		sort();//Llamada a la funcion que ordena el array
		setNewRank(toIns);//Llamada a la funcion que pone al nuevo jugador en la posicion del array pertinente

		std::ofstream writeFile("../res/Ranking.bin", ios::binary);
		//Escribimos el array en el fichero binario
		for (int i = 0; i < 10; i++) {
			writeFile.write(top10[i].name.c_str(), top10[i].name.size());
			writeFile.write("\0", sizeof(char));
			writeFile.write(reinterpret_cast<char*>(&top10[i].score), sizeof(top10[i].score));
		}
		writeFile.close();

	}
	//Funcion que devuelbe un array con el contenido del fichero
	HighScores readBin() {
		std::ifstream readFile("../res/Ranking.bin", ios::binary);

		HighScores retRank[10];
		for (int i = 0; i < 10; i++) {
			std::getline(readFile, retRank[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&retRank[i].score), sizeof(retRank[i].score));
		}
		readFile.close();
		return retRank[10];
	}
	//Funcion que printa por consola el contenido del fichero(usada solo para comprobar que funciona)
	void readBinCons() {
		std::ifstream readFile("../res/Ranking.bin", ios::binary);

		HighScores rankPrint[10];
		for (int i = 0; i < 10; i++) {
			std::getline(readFile, rankPrint[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&rankPrint[i].score), sizeof(rankPrint[i].score));
			std::cout << i + 1 << "-Player name: " << rankPrint[i].name << "-Player score: " << rankPrint[i].score << std::endl;
		}
		readFile.close();
	}

}