#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Component;
class GameObject;

class ObjectFile
{
public:
	ObjectFile(std::string filename);

	//reads data for a specific properties from a file, given a tag and list of types.
	//example: int a, b, c; file.read_properties("ThreeInts", a, b, c);
	template<typename ... params>
	void read_properties(std::string tag, params& ... args) {
		reset_cursor();
		std::string line;
		while (std::getline(file_, line))
		{
			std::istringstream ss(line);
			std::string cName;
			ss >> cName; //read descriptor token
			if (cName != tag)
			{
				continue;
			}
			else
			{
				recursive_read_tagged_value(ss, args...);
				break;
			}
		}
	}

	//constructs components from the file by name, if they were registered.
	//This FULLY constructs the components, including setting their parent.
	//The calling GameObject need only store the components in its list.
	std::vector<Component*> construct_components(GameObject* parent);

private:
	template <typename T, typename ... U>
	void recursive_read_tagged_value(std::istringstream& ss, T& first, U& ... args){
		//extract one value and continue
		read_tagged_value(ss, first);
		recursive_read_tagged_value(ss, args...);
	}

	template <typename T> //called at end of read list
	void recursive_read_tagged_value(std::istringstream& ss, T& last) { read_tagged_value(ss, last); }

	template<typename T>
	void read_tagged_value(std::istringstream& ss, T& val) { //scroll to next line and read value
		std::string curLine;
		std::getline(file_, curLine);
		ss = std::istringstream(curLine);
		std::string tag; //throw away 'tag' value
		ss >> tag >> val;
	}

	void reset_cursor();
	std::ifstream file_;
};