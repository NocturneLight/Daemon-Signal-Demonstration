//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#include "globalMap.h"
#include "sharedVar.h"

//Initialize variables here.
//Null, because instance will be initialized on demand.
mapSingleton* mapSingleton::instance = 0;
std::map<int, std::string> optionMap;

mapSingleton* mapSingleton::getInstance()
{
  if (instance == 0)
  {
    instance = new mapSingleton();
  }

  return instance;
}

void mapSingleton::insert(int index, std::string value)
{
  //Insert a single value to the map.
  optionMap[index] = value;
}

void mapSingleton::view()
{
  //View a single index of the map.
  //std::cout << optionMap[index] << std::endl;

  //View all of the map.
  for (std::size_t i = 0; i < sizeof(optionMap); i++)
  {
    std::cout << optionMap[i] << std::endl;
  }
}

std::string mapSingleton::returnVar(int value)
{
  return optionMap[value];
}

std::map<int, std::string> mapSingleton::returnMap()
{
  return optionMap;
}

mapSingleton::mapSingleton(){}

