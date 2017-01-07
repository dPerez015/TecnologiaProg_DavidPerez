#pragma once
#include <XML\rapidxml_print.hpp>
#include<XML\rapidxml_utils.hpp>
#include "stdio.h"

using namespace rapidxml;
using namespace std;

namespace IOManager {

	void FilesXML(string &&filename) {
		xml_document<> doc;
		ifstream file(filename);

		vector<char>buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		buffer.push_back('\0');

		doc.parse<0>(&buffer[0]);

		cout << "First node: " << doc.first_node()->name() << endl;
		xml_node<> *rootNode = doc.first_node();
		for (xml_node<> *nextNode = rootNode->first_node(); nextNode; nextNode = nextNode->next_sibling()) {
			cout << nextNode->name() << ":" << nextNode->value() << endl;
		}
	}

}