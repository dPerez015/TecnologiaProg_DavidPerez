#include "GameEngine.h"
#include <iostream>
int main(int argc, char* args[]) {
	std::string playerName;
	std::cout << "Introduce tu nickname:" << std::endl;
	std::cin >> playerName;
	GameEngine::Run("MyGame", 1000, 1000, playerName);

	return 0;
}
