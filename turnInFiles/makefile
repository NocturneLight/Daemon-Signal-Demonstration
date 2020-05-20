#Name: Antonio Rios
#Email: alr150630@utdallas.edu
#Course Number: 3376.001


#Declare compiler, flags, libraries and library paths here.
CXX = g++
CPPFLAGS = -Wall -O -I /home/012/a/al/alr150630/HomeworkFive/rudeconfig/include -I /home/012/a/al/alr150630/HomeworkFive/include
LDFLAGS = /home/012/a/al/alr150630/HomeworkFive/rudeconfig/lib/librudeconfig.a #Normally would use -L and give a path to lib.
#LDLIBS = -lrudeconfig #Would normally use, but like for LDFLAGS, we've doing it differently because UTD didn't install the right stuff onto the linux server.

#Store our file names here.
EXEC = foDaemon.exe
CFILE = $(wildcard *.cc)
OFILE = $(CFILE:.cc=.o)

#Create the executable file.
$(EXEC): $(OFILE)
	$(CXX) $(OFILE) $(LDFLAGS) -o $(EXEC) 

#Remove unnecessary files.
clean: 
	rm -f *.o *~
