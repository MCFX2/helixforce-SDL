#include "fileman.h"
#include <iostream>
#include <fstream>

#include "ComponentRegistry.h"

ObjectFile::ObjectFile(std::string filename) : file_("./data/object/" + filename)
{
}

std::vector<Component*> ObjectFile::construct_components(GameObject* parent)
{
	reset_cursor();
	std::vector<Component*> constructed_components;
	//we build the list of components to construct first, then actually construct them all at once last.
	//this is done because actually constructing the components might fuck with our file cursor.
	std::vector<std::string> component_list;
	std::string curLine;
	while (std::getline(file_, curLine))
	{ //first determine if line refers to a component
		if (curLine.empty()) continue;
		if (std::isalpha(curLine.at(0)))
		{ //if line starts with a letter, assume it is a componenet
			component_list.push_back(curLine);
		}
	}

	for (std::string& component_tag : component_list)
	{
		constructed_components.push_back(ComponentRegistry::MakeComponent(component_tag, parent));
	}

	return constructed_components;
}

void ObjectFile::reset_cursor()
{
	file_.clear(); //reset bad state (in case eof was hit)
	file_.seekg(0); //seek to beginning
}
