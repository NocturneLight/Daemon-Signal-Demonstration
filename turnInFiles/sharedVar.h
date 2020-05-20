//Name: Antonio Rios
//Email: alr150630@utdallas.edu
//Course Number: 3376.001

#ifndef SHAREDVAR_H
#define SHAREDVAR_H

#include <string>
#include <vector>
#include <map>

//Create our function prototypes here.
std::vector<std::string> &parseLine(int argc, char* argv[]);
int parseConf();
int programMode(char* argv[]);
void recheckConfig();
void handleSignal(int signal);
void notify();
void backupLimit(std::string name);

//Put global variables here.
extern bool daemonValue;
extern FILE *logFile;

#endif
