#pragma once
#include "XML\rapidxml.hpp"
#include "XML\rapidxml_utils.hpp"
#include <vector>
//#include <iostream>

namespace IOManager {

	int FilesXML(std::string &&filename, std::string &&nodename) {

		rapidxml::xml_document<> doc;//Crea el documento que contiendra el DOM tree para el fichero XML
		std::ifstream file(RESOURCE_FILE(filename));//Carga el fichero XML pertinente
		//Convierte el XML en un vector
		std::vector<char>buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');
		//Parsing(Analisis) del contenido del fichero
		doc.parse<0>(&buffer[0]);

		//Variable con el primer nodo
		rapidxml::xml_node<> *rootNode = doc.first_node("Stadistics");
		const char *orgValue;//Variable que obtiene el valor del nodo seleccionado
		int toGetValue;//variable para return
		const char *nodeUsed = nodename.c_str();//Variable que covierte el string en const char
		//Se guarda el valor de un nodo predeterminado de XML en un int
		for (rapidxml::xml_node<> *nextNode = rootNode->first_node(); nextNode; nextNode = nextNode->next_sibling()) {
			rapidxml::xml_node<> *nodeValue = nextNode->first_node(nodeUsed);
			orgValue = nodeValue->value();
			toGetValue = atoi(orgValue);
			return toGetValue;
			}
		}
	}
