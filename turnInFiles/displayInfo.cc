//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#include "sharedVar.h"
#include "globalMap.h"
#include <syslog.h>

int main(int argc, char* argv[])
{
  //new mapSingleton(); //This will not work.

  //Create an instance of mapSingleton so that we may use the global map.
  mapSingleton* mapContents = mapSingleton::getInstance();
  
  //Parse the command line using TCLAP, return the vector containing
  //the parsed information, and store that to a variable for now.
  std::vector<std::string> parsedResults(parseLine(argc, argv));

  //Take the vector contents stored in parsedResults and insert them into 
  //the map for later use.
  mapContents->insert(modeIndex, parsedResults[modeIndex]);
  mapContents->insert(fileNameIndex, parsedResults[fileNameIndex]);

  //rudeConfig is not as picky as TCLAP, so call parseConf and it will 
  //parse the configuration file and add that information to the map.
  parseConf();
  
  //Determine whether we should be a regular program or a daemon.
  programMode(argv);

  return 0;
}
