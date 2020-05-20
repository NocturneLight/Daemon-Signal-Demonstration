//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#include <iostream>
#include <vector>
#include "sharedVar.h"
#include "globalMap.h"
#include "tclap/CmdLine.h"
#include "tclap/SwitchArg.h"
#include "tclap/UnlabeledValueArg.h"


//Initialize our variables.
std::vector<std::string> parsedInfo;
mapSingleton* tclapInstance = mapSingleton::getInstance();

std::vector<std::string> &parseLine(int argc, char* argv[])
{  
  try
  {
    //Define our arguments here.
    TCLAP::CmdLine command("CS 3376.001 Homework Five", ' ', "1.0");
    TCLAP::SwitchArg runMode("d", "daemon", "Run in daemon mode (forks to run as a daemon).", command, false);
    TCLAP::ValueArg<std::string> configFileArg("c", "configfile", "The name of the configuration file.", false, "CS3376dirmond.conf", "config filename");

    //Add the arguments to command here.
    command.add(configFileArg);

    //Parse the array here.
    command.parse(argc, argv);
    
    //Add the parsed results to a vector.
    parsedInfo.push_back(runMode.getValue()? "True" : "False");    
    parsedInfo.push_back(configFileArg.getValue());
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }

  return parsedInfo;
}
