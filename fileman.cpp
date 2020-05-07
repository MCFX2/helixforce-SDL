#include "fileman.h"
#include <iostream>
#include <fstream>

#include "ComponentRegistry.h"

ObjectFile::ObjectFile(std::string filename) : file_("./data/" + filename)
{
}

std::vector<Component*> ObjectFile::construct_components(GameObject* parent)
{
	reset_cursor();
	std::vector<Component*> constructed_components;
	std::string curLine;
	while (std::getline(file_, curLine))
	{ //first determine if line refers to a component
		
		if (std::isalpha(curLine.at(0)))
		{ //if line starts with a letter, assume it is a componenet
			constructed_components.push_back(ComponentRegistry::MakeComponent(curLine, parent));
		}
	}

	return constructed_components;
}

void ObjectFile::reset_cursor()
{
	file_.clear(); //reset bad state (in case eof was hit)
	file_.seekg(0); //seek to beginning
}
