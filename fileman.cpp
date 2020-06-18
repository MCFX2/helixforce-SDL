#include "fileman.h"
#include <iostream>
#include <fstream>

#include <algorithm>

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
	//this pair is a component name tied to a list of property strings to read
	using build_instructions = std::pair<std::string, std::vector<std::string>>;
	std::vector<build_instructions> component_list;
	std::string curLine;
	std::getline(file_, curLine);
	while (!file_.eof())
	{ //first determine if line refers to a component
		if (curLine.empty())
		{
			std::getline(file_, curLine);
			continue;
		}
		if (std::isalpha(curLine.at(0)))
		{ //if line starts with a letter, assume it is a component
			std::transform(curLine.begin(), curLine.end(), curLine.begin(), std::toupper); //convert to upper case prior to storing
			std::string curComponent = curLine;
			std::vector<std::string> curProperties;
			while (std::getline(file_, curLine))
			{ //now keep reading for properties
				if (curLine.empty()) continue;
				if (std::isalpha(curLine.at(0)))
				{ //if first character start with a letter, assume we are at the end of our property list
					break;
				}
				std::transform(curLine.begin(), curLine.end(), curLine.begin(), std::toupper);
				curProperties.push_back(curLine);
			}
			component_list.push_back(std::make_pair(curComponent, curProperties));
		}
	}

	for (build_instructions& instructions : component_list)
	{
		Component* component = ComponentRegistry::MakeComponent(instructions.first, parent);
		for (std::string& prop : instructions.second)
		{
			std::istringstream prop_read(prop);
			std::string prop_tag;
			prop_read >> prop_tag;
			if (prop_tag.empty())
			{ //no property found, skip
				continue;
			}
			//strip off trailing : character
			prop_tag.pop_back();
			ComponentRegistry::Property_Setter_Func fn = ComponentRegistry::SetProperty(instructions.first, prop_tag);
			if (fn)
			{
				fn(component, prop_read);
			}
		}
		constructed_components.push_back(component);
	}

	return constructed_components;
}

void ObjectFile::reset_cursor()
{
	file_.clear(); //reset bad state (in case eof was hit)
	file_.seekg(0); //seek to beginning
}
