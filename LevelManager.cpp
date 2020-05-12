#include "LevelManager.h"

#include <unordered_map>

static std::unordered_map<std::string, Level*> Level_Dict;

void LevelManager::Register_Level(Level* level)
{
	Level_Dict.emplace(level->name, level);
}
