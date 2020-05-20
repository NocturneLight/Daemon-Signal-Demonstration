//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <map>
#include <sys/inotify.h>
#include <limits.h>
#include "sharedVar.h"
#include "globalMap.h"
#include "rude/config.h"

//Put files or variables that will be used by multiple functions here.
FILE *logFile = NULL;
mapSingleton* mainInstance = mapSingleton::getInstance();
bool daemonValue = false;

int programMode(char* argv[])
{
  //Define variables that will be used by both modes here.
  std::stringstream pidString;
  std::stringstream logString;
  FILE *pidFile = NULL;
  pid_t processID = 0;
  pid_t sessionID = 0;


  if (mainInstance->returnVar(modeIndex) == "True")
  {
    std::cout << "Entering Daemon Mode." << std::endl;

    //Create a child process.
    processID = fork();

    //Let user know the fork() failed.
    if (processID < 0)
    {
      if (mainInstance->returnVar(verboseIndex) == "true")
      {
	std::cout << "The fork failed for one reason or another." << std::endl;
      }
      exit(-1);
    }

    //Kill the parent process.
    if (processID > 0)
    {
      if (mainInstance->returnVar(verboseIndex) == "true")
      {
	std::cout << "We've killed the parent." << std::endl;
      }
      exit(0);
    }
  
    //Unmask the file mode.
    umask(0);

    //Set a new session ID.
    sessionID = setsid();

    if (sessionID < 0)
    {
      //Return failure.
      exit(-1);
    }
  }
  else if (mainInstance->returnVar(modeIndex) == "False") 
  {
    std::cout << "Entering Shell Mode." << std::endl;
  }

  //Open up the log file.
  logFile = fopen(mainInstance->returnVar(logfileIndex).c_str(), "w+");

  if (mainInstance->returnVar(verboseIndex) == "true")
  {
    std::cout << "Log file opened. All messages will be redirected to there." << std::endl;
  }

  //Change the working directory to the test directory.
  chdir("/home/012/a/al/alr150630/HomeworkFive/testdir");

  if (mainInstance->returnVar(verboseIndex) == "true")
  {
    fprintf(logFile, "Successfully changed to the specified watch directory.\n");
    fflush(logFile);
  }

  //Close stdin, stdout, and stderr.
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
    
  if (mainInstance->returnVar(verboseIndex) == "true")
  {
    fprintf(logFile, "stdout, stdin, and stderr, have all been successfully closed.\n");
    fflush(logFile);
  }

  //Check if a pid file exists already and exit the program if it does.
  //Otherwise, create the pid file, get the pid, convert to c*, 
  //and then store the pid inside the newly formed file.
  if (std::ifstream("CS3376dirmond.pid"))
  {
    logString << mainInstance->returnVar(logfileIndex);
    fprintf(logFile, "A pid file already exists. Exiting the daemon.\n");
    exit(-1);
  }
  else
  {
    pidString << getpid();
    pidFile = fopen("CS3376dirmond.pid", "w+");
    fprintf(pidFile, pidString.str().c_str());
    fflush(pidFile);
  }

  //If we get any of these signals, enter the handleSignal function.    
  signal(SIGINT, handleSignal);
  signal(SIGTERM, handleSignal);
  signal(SIGHUP, handleSignal);

  //Do all our daemon work inside the while loop.
  while(1)
  {
    daemonValue = true;

    //Create the .versions folder if it doesn't already exist.
    mkdir(".versions", 0700);

    //Run inotify during the loop to observe changes in the folder.
    notify();

    //Sleep for 1 second.
    sleep(1);
  }

  return 0;
}


