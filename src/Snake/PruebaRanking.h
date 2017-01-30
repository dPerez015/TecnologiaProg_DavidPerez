#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using std::ios;
//Aquest és el codi que havia d'utilitzar en principi però hem donava error
namespace BinaryFiles {

	struct HighScores {
		std::string name;
		int score;
	};

	void writeBinary(std::string name, int score) {//Aquesta unica funció s'he n'encarrega de (o s'encarregava) de llegir un fitxer binari per guardar-se les seves dades en un vector, per derprés guardar-se les dades noves dins d'aquest vector i ordenar-les per després poder escriure-les al fitxer binari

		std::vector<HighScores> bests;

		std::ifstream readFile("../res/Ranking.dat", ios::binary);
		readFile.seekg(0, ios::end);
		int sizeFile = (int)readFile.tellg();
		readFile.seekg(0, ios::beg);

		while (readFile.tellg() < sizeFile) {

			HighScores tmp;

			std::getline(readFile, name, '\0');
			tmp.name = name;
			readFile.read(reinterpret_cast<char*>(&score), sizeof(score));
			tmp.score = score;
			bests.emplace(bests.end(), tmp);
		}

		readFile.close();

		/*HighScores toIns;
		toIns.name = name;
		toIns.score = score;
		for (int i = 0; i < 10; i++) {
		if (bests[i].score < score) {
		for (int j = 10 - 1; j > i; j--) {
		bests[j] = bests[j - 1];
		}
		bests[i] = toIns;
		}
		}*/

		if (bests.size() > 10) {
			bests.pop_back();
		}

		std::ofstream writeFile("../res/Ranking.dat", ios::binary);

		for (int i = 0; i < 10; i++) {
			writeFile.write(bests[i].name.c_str(), bests[i].name.size());
			writeFile.write("\0", sizeof(char));
			writeFile.write(reinterpret_cast<char*>(&bests[i].score), sizeof(bests[i].score));
		}
		writeFile.close();

	}

}

