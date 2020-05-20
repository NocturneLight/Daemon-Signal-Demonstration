Type "./foDaemon.exe -d" to enter Daemon Mode.

Type "./foDaemon.exe" to enter regular mode. In regular mode, I suggest opening a 
second shell.

The .pid file is in the testdir directory.

Copy the .pid number in there and in a shell type "kill -SIGINT (pidnumber)" or 
"kill -SIGTERM (pidnumber)" to kill the program.

Type "kill -SIGHUP (pidnumber)" to update the program with the .conf's new settings.

Edit any file in the testdir folder to create a backup in the .include folder.

I was unable to limit the number of backups using the number in the .conf file. I ran
out of time.

The .log file is in the turnInFiles folder along with the rest of the source files.
