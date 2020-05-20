//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#include "sharedVar.h"
#include "globalMap.h"
#include <fstream>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sstream>
#include <sys/inotify.h>
#include <dirent.h>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <algorithm>
#include <iterator>

void handleSignal(int signal)
{
  mapSingleton* signalInstance = mapSingleton::getInstance();

  if (signal == SIGHUP)
  {
    //Update the map with any changes to the config file.
    recheckConfig();
  }
  else if (signal == SIGINT || signal == SIGTERM)
  {
    //Inform the user that we're killing the daemon.
    fprintf(logFile, "Proceeding to kill the daemon.\n");
    fflush(logFile);

    //Remove the pid file.
    remove("CS3376dirmond.pid");

    if (signalInstance->returnVar(verboseIndex) == "true")
    {
      fprintf(logFile, ".pid file successfully removed.\n");
      fflush(logFile);
    }

    //Close the log file.
    fclose(logFile);

    //Exit the program.
    exit(0);
  }
}

void recheckConfig()
{
  //Change the directory to turnInFiles so that we may have access to the source code. 
  chdir("/home/012/a/al/alr150630/HomeworkFive/turnInFiles");

  //Parse the configuration file again.
  parseConf();

  //When finished change the directory back to testdir.
  chdir("/home/012/a/al/alr150630/HomeworkFive/testdir");
}

void notify()
{
  //Define any important numbers and other things that don't fit variables here.
  #define MAX_EVENTS 1024 //Maximum number of events to process at once.
  #define LENGTH_NAME 16 //Assume the length of the filename won't exceed 16 bytes.
  #define EVENT_SIZE (sizeof (struct inotify_event)) //Size of one event.
  #define BUFFER_LENGTH (MAX_EVENTS * (EVENT_SIZE + LENGTH_NAME)) //Buffer to store data of events.

  //Initialize any variables here.
  mapSingleton* notifyInstance = mapSingleton::getInstance();
  std::stringstream createString;
  std::string newString;
  int length;
  int wd = 0;
  int fd = 0;
  int i = 0;
  char buffer[BUFFER_LENGTH];

  //Initialize inotify.
  fd = inotify_init();

  //If we screwed up badly, print to the log file that we failed.
  if (fd < 0)
  {
    fprintf(logFile, "Failed to initialize inotify.\n");
    fflush(logFile);
  }

  //Add to watch directory.
  wd = inotify_add_watch(fd, notifyInstance->returnVar(watchdirIndex).c_str(), IN_MODIFY);

  //i is now needed, so set it to 0.
  i = 0;

  //Get the length and store it in length.
  length = read(fd, buffer, BUFFER_LENGTH);

  //If we massively screwed up, print read and confuse everyone.
  if (length < 0)
  {
    fprintf(logFile, "read");
    fflush(logFile);
  }


  while (i < length)
  {
    //Create our structure.
    struct inotify_event *event = (struct inotify_event*) &buffer[i];

    //The core of the notification system.
    if (event->len)
    {
      if (event->mask & IN_MODIFY)
      {
        if (event->mask & IN_ISDIR)
	{
          //If a directory was modified, print to the log file saying that.
	  fprintf(logFile, "The directory %s has been modified.\n", event->name);
	  fflush(logFile);
	}
        else
	{
          //If a file was modified, create a new string using the name of the modified file.
	  createString << "cp " << event->name << " .versions/" << event->name << ".$(date +%F_%R)";
	  newString = createString.str();

	  //Notify the user that we will creating a backup.
	  fprintf(logFile, "Moving a copy of %s to the .versions folder.\n", event->name);
	  fflush(logFile);

	  //Use system() to issue the cp command. We shouldn't use a command as dangerous as system(), but we're low on time.
	  system(newString.c_str());

          //backupLimit(event->name);
	}
      }
    }

    //Increase i so we can escape the loop.
    i += EVENT_SIZE + event->len;
  }

  //Close everything.
  (void)inotify_rm_watch(fd, wd);
  (void)close(fd);
}

void backupLimit(std::string name)
{
  //Create our variables and such here.
  std::vector<std::string> fileVector;
  FILE* command;
  std::stringstream deleteStream;
  std::string deleteString;
  mapSingleton* backupInstance = mapSingleton::getInstance();
  char buffer[1024];  

  command = popen("ls -l .versions", "r");

  if (command == NULL)
  {
    fprintf(logFile, "Failed to open the pipe.\n");
    exit(-1);
  }

  while(fgets(buffer, 1024, command))
  {
    std::string fileVectorString = buffer;
    fileVector.push_back(fileVectorString);
  }

  pclose(command);

  sort(fileVector.begin(), fileVector.end());

  if (fileVector.size() > (size_t)atoi(backupInstance->returnVar(numversionsIndex).c_str()))
  {
    while (fileVector.size() > (size_t)atoi(backupInstance->returnVar(numversionsIndex).c_str()))
    {
      deleteStream << "ls -l" << fileVector.back();
      deleteString = deleteStream.str();

      system(deleteString.c_str());

      fileVector.pop_back();
    }
  }
}
