//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001


#ifndef GLOBALMAP_H
#define GLOBALMAP_H


#include <map>
#include <iostream>

//Initialize any variables or anything else here.
enum commandList {modeIndex, fileNameIndex, verboseIndex, logfileIndex, passwordIndex, numversionsIndex, watchdirIndex};

class mapSingleton
{
  private:
    //The stored instance.
    static mapSingleton* instance;

    //Private constructor to prevent instancing from occuring.
    mapSingleton();

  public:
    //Static access method.
    static mapSingleton* getInstance();

    //Methods to insert and view the map.
    void insert(int index, std::string value);
    void view();
    std::string returnVar(int value);
    std::map<int, std::string> returnMap();
    std::map<int, std::string> optionMap;
};

#endif
