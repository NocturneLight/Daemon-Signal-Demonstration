//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "rude/config.h"
#include "sharedVar.h"
#include "globalMap.h"

int parseConf()
{
  //Initialize anything here.
  rude::Config config;
  mapSingleton* rudeInstance = mapSingleton::getInstance();
  extern bool daemonValue;
  std::vector<std::string> rudeVector;

  //Load the configuration file to begin parsing.
  if(config.load(rudeInstance->returnVar(fileNameIndex).c_str()))
  {
    //Set the section for Parameter.
    config.setSection("Parameter");

    //Check if the required information exists and store it in the map, otherwise throw an error and quit.
    if (config.exists("Verbose") && config.exists("LogFile") && config.exists("Password") && config.exists("NumVersions") && config.exists("WatchDir"))
    {
      if (config.exists("Verbose"))
      {
	rudeInstance->insert(verboseIndex, config.getStringValue("Verbose"));
      }
      else
      {
	if (!daemonValue)
	{
	  std::cerr << "Missing parameters in the configuration file. Please provide the correct parameters and try again." << std::endl;
	  exit(-1);
	}
	else if (daemonValue)
        {
	  fprintf(logFile, "Missing parameters in the configuration file. Please provide the correct parameters and try again.\n");
	  fflush(logFile);
	}
      }

      if (config.exists("LogFile"))
      {
	rudeInstance->insert(logfileIndex, config.getStringValue("LogFile"));
      }
      else
      {
        if (!daemonValue)
	{
	  std::cerr << "Missing parameters in the configuration file. Please provide the correct parameters and try again." << std::endl;
	  exit(-1);
	}
	else if (daemonValue)
        {
	  fprintf(logFile, "Missing parameters in the configuration file. Please provide the correct parameters and try again.\n");
	  fflush(logFile);
	}
      }

      if (config.exists("Password"))
      {
	if (rudeInstance->returnVar(passwordIndex) == "")
	{
	  rudeInstance->insert(passwordIndex, config.getStringValue("Password"));
        }
      }
      else
      {
	if (!daemonValue)
	{
	  std::cerr << "Missing parameters in the configuration file. Please provide the correct parameters and try again." << std::endl;
	  exit(-1);
	}
	else if (daemonValue)
	{
	  fprintf(logFile, "Missing parameters in the configuration file. Please provide the correct parameters and try again.\n");
	  fflush(logFile);
	}
      }

      if (config.exists("NumVersions"))
      {
	rudeInstance->insert(numversionsIndex, config.getStringValue("NumVersions"));
      }
      else
      {
	if (!daemonValue)
	{
	  std::cerr << "Missing parameters in the configuration file. Please provide the correct parameters and try again." << std::endl;
	  exit(-1);
	}
	else if (daemonValue)
	{
	  fprintf(logFile, "Missing parameters in the configuration file. Please provide the correct parameters and try again.\n");
	  fflush(logFile);
	}
      }

      if (config.exists("WatchDir"))
      {
	if (rudeInstance->returnVar(watchdirIndex) == "")
	  {
	    rudeInstance->insert(watchdirIndex, config.getStringValue("WatchDir"));
	  }
      }
      else
      {
	if (!daemonValue)
	{
	  std::cerr << "Missing parameters in the configuration file. Please provide the correct parameters and try again." << std::endl;
	  exit(-1);
	}
	else if (daemonValue) 
	{
	  fprintf(logFile, "Missing parameters in the configuration file. Please provide the correct parameters and try again.\n");
	  fflush(logFile);
	}
      }

      if (rudeInstance->returnVar(verboseIndex) == "true")
      {
	if (daemonValue)
	{
	  fprintf(logFile, "Successfully parsed the .conf file!\n");
	  fflush(logFile);
	}
	else if (!daemonValue)
	{
	  std::cout << "Successfully parsed the .conf file!" << std::endl;
	}
      }

    }
    else
    {
      if (!daemonValue)
      {
	std::cerr << "Missing configuration file. Please provide a file and try again." << std::endl;
	exit(-1);
      }
      else if (daemonValue)
      {
	fprintf(logFile, "Missing configuration file. Please provide a file and try again.\n");
	fflush(logFile);
      }
    }
  }

  return 0;
}


