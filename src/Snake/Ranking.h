#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using std::ios;
//Últim codi que hem vist, aquest és el del vector predeterminat
namespace BinaryReadWrite {

	struct PlayerScore
	{
		std::string name;
		int score;

	};

	void sort(std::vector<PlayerScore> &rankToSort) {//Ordena el vector que se li passi

		PlayerScore tmp;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (rankToSort[i].score > rankToSort[j].score) {
					tmp = rankToSort[i];
					rankToSort[i] = rankToSort[j];
					rankToSort[j] = tmp;
				}
			}
		}

	}

	void writeBin(std::vector<PlayerScore> playerStats) {//Escriu el vector que se li passa en un fitxer binari
		std::ofstream writeFile("../res/Ranking.bin", ios::binary);

		for (int i = 0; i < 10; i++) {
			writeFile.write(playerStats[i].name.c_str(), playerStats[i].name.size());
			writeFile.write("\0", sizeof(char));
			writeFile.write(reinterpret_cast<char*>(&playerStats[i].score), sizeof(playerStats[i].score));
		}
		writeFile.close();
	}

	std::vector<PlayerScore> readBin() {//Retorna un vector amb la info del fitxer binari
		std::ifstream readFile("../res/Ranking.bin", ios::binary);

		std::vector<PlayerScore> ranking;

		std::cout << "Players ranking: " << std::endl;
		for (int i = 0; i < 10; i++) {
			std::getline(readFile, ranking[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&ranking[i].score), sizeof(ranking[i].score));
		}
		readFile.close();
		return ranking;
	}


	void mainFunct() {//Es crea un fitxer binari predeterminat de 10 pos que es passarà a les funcions anteriors

		PlayerScore ply1 = { "Player", 0 };
		PlayerScore ply2 = { "Player", 0 };
		PlayerScore ply3 = { "Player", 0 };
		PlayerScore ply4 = { "Player", 0 };
		PlayerScore ply5 = { "Player", 0 };
		PlayerScore ply6 = { "Player", 0 };
		PlayerScore ply7 = { "Player", 0 };
		PlayerScore ply8 = { "Player", 0 };
		PlayerScore ply9 = { "Player", 0 };
		PlayerScore ply10 = { "Player", 0 };

		std::vector<PlayerScore> rankPlay = { ply1, ply2, ply3, ply4, ply5, ply6, ply7, ply8, ply9, ply10 };

		if (rankPlay.size() > 10) {
			rankPlay.pop_back();
		}

		sort(rankPlay);
		writeBin(rankPlay);
		readBin();
	}
}