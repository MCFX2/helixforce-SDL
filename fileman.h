#pragma once

#include <string>
#include <map>

class ObjectStream
{
public:
	//you must register your type if you want it to be readable (see Sprite.cpp and Sprite.h)


	ObjectStream(std::string filename);
	~ObjectStream();

	template<typename ... params>
	void read(params& ...)
	{

	}

private:
	FILE* file_;
};