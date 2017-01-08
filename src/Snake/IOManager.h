#pragma once
#include "XML\rapidxml.hpp"
#include "XML\rapidxml_utils.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace IOManager {

	void FilesXML(std::string &&filename) {

		rapidxml::xml_document<> doc;//Crea el documento que contiendra el DOM tree para el fichero XML
		std::ifstream file(filename);//Carga el fichero XML pertinente
		//Convierte el XML en un vector
		std::vector<char>buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		doc.parse<0>(&buffer[0]);//Parsing(Analisis) del contenido del fichero
		//Variable con el primer nodo
		rapidxml::xml_node<> *rootNode = doc.first_node("Stadistics");
		//Imprime el contenido de XML
		std::cout << "This is the first node: " << rootNode->name() << std::endl;
		for (rapidxml::xml_node<> *nextNode = rootNode->first_node(); nextNode; nextNode = nextNode->next_sibling()) {
			
			std::cout << nextNode->name() << ":" << std::endl;

			for (rapidxml::xml_node<> *innerNxtNode = nextNode->first_node(); innerNxtNode; innerNxtNode = innerNxtNode->next_sibling()) {

				std::cout << innerNxtNode->name() << ":" << innerNxtNode->value() << std::endl;

			}
		}
	}

}